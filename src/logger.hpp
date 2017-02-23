#ifndef CPP_BASE_LOGGER_HPP
#define CPP_BASE_LOGGER_HPP

#include <execinfo.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <functional>
#include <string>
#include <vector>

#define NONRET __attribute__((noreturn))
#define UNUSED __attribute__((unused))
#define GENERATE_PRINTF_WARNINGS __attribute__((format(printf, 1, 2)))

namespace Base {

void NONRET __attribute__((format(printf, 1, 2))) Die(const char* msg, ...);

int verbose_level = 0;
int msg_fd = 2;
int die_fd = 2;

static const int kDieBufferSize = 1 << 13;
static const int kDieStackSize = 50;

std::function<void(std::string)> DieExitFunction;

std::vector<std::string> GetCallStack() {
    void* void_stack[kDieStackSize];  // stack len

    size_t stack_size = backtrace(void_stack, sizeof(void_stack));
    char** string_stack = backtrace_symbols(void_stack, stack_size);

    std::vector<std::string> stack;
    for (size_t i = 0; i < stack_size; i += 1) {
        stack.push_back(string_stack[i]);
    }

    free(string_stack);
    return stack;
}

void xwrite(int fd, const char* head, int remaining) {
    while (1) {
        int len = write(fd, head, remaining);  /// hope it doesn't crash somehow
        if (len == -1) {
            if (errno == EINTR) {
                continue;
            } else {
                break;
            }
        } else {
            head += len;
            remaining -= len;
            if (remaining == 0) {
                break;
            }
        }
    }
}

std::string EscapeQuotes(const char* msg) {
    std::string result = "";
    while (*msg != '\0') {
        if (*msg == '\"') {
            result += "\\\"";
        } else if (*msg == '\'') {
            result += "\\\'";
        } else {
            result += *msg;
        }
        msg++;
    }
    return result;
}

void NONRET Die(const char* field_name, const char* msg, bool is_json_object) {
    std::string json = "{";

    json += "\"" + std::string(field_name) + "\":";
    if (is_json_object) {
        json += std::string(msg);
    } else {
        json += "\"" + EscapeQuotes(msg) + "\"";
    }

    json += ",\n";
    json += "\"callstack\":[\n";

    auto call_stack = GetCallStack();
    for (auto& itr : call_stack) {
        json += "    \"" + itr + "\",\n";
    }

    if (call_stack.size()) {
        json.pop_back();  // remove last \n
        json.pop_back();  // remove last ,
        json += "\n";
    }

    json += "]}\n";

    /// write errors to die_fd first
    xwrite(die_fd, json.c_str(), json.size());

    if (DieExitFunction) {
        DieExitFunction(json);
    }

    close(die_fd);
    exit(2);
}

/* Report an error of the sandbox itself */
void NONRET __attribute__((format(printf, 1, 2))) Die(const char* msg, ...) {
    va_list args;
    va_start(args, msg);
    char buff[kDieBufferSize];
    int n = vsnprintf(buff, sizeof(buff) - 1, msg, args);
    buff[n] = '\0';

    Die("message", buff, false);
}

void DieLogToFile(const std::string& file_path) {
    int fd = open(file_path.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0777);
    if (fd == -1) {
        Die("Cant redirect Die log's to file: %s", file_path.c_str());
    }
    die_fd = fd;
}

void __attribute__((format(printf, 2, 3))) Msg(int verbosity, const char* msg, ...) {
    va_list args;
    va_start(args, msg);

    if (verbosity <= verbose_level) {
        vdprintf(msg_fd, msg, args);
    }

    va_end(args);

    if (msg[strlen(msg) - 1] == '\n') {
        fsync(msg_fd);
    }
}

void __attribute__((format(printf, 1, 2))) Msg(const char* msg, ...) {
    va_list args;
    va_start(args, msg);

    if (1 <= verbose_level) {
        vdprintf(msg_fd, msg, args);
    }

    va_end(args);

    if (msg[strlen(msg) - 1] == '\n') {
        fsync(msg_fd);
    }
}

}  // namespace Base

#endif
