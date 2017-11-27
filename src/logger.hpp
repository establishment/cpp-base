#ifndef CPP_BASE_LOGGER_HPP
#define CPP_BASE_LOGGER_HPP

#include <functional>
#include <string>
#include <vector>

#include "utils.hpp"

namespace Base {

void NONRET __attribute__((format(printf, 1, 2))) Die(const char* msg, ...);

extern std::function<void(std::string)> DieExitFunction;

std::vector<std::string> GetCallStack();

void xwrite(int fd, const char* head, int remaining);

std::string EscapeQuotes(const char* msg);

void NONRET Die(const char* field_name, const char* msg, bool is_json_object);

/* Report an error of the sandbox itself */
void NONRET __attribute__((format(printf, 1, 2))) Die(const char* msg, ...);

void DieLogToFile(const std::string& file_path);

void __attribute__((format(printf, 2, 3))) Msg(int verbosity, const char* msg, ...);

void __attribute__((format(printf, 1, 2))) Msg(const char* msg, ...);

}  // namespace Base

#endif // CPP_BASE_LOGGER_HPP
