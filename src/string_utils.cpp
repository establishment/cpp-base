#include "string_utils.hpp"

#include <string.h>
#include <fstream>
#include <string>
#include <vector>

namespace Base {
bool NeedsEscape(char c) {
    static std::string escaped_characters = " \n\t\r\f\"\'";
    for (char itr : escaped_characters) {
        if (itr == c) {
            return true;
        }
    }
    return false;
}

bool IsWhitespace(char c) {
    static std::string whitespaces = " \n\t\r\f";
    for (char itr : whitespaces) {
        if (itr == c) {
            return true;
        }
    }

    return false;
}

std::vector<std::string> ParseCommandLine(const std::string& txt) {
    std::string current_txt = "";
    std::vector<std::string> output;
    bool quotes = false;
    bool was_quoted = false;
    char quote_char = '\0';
    bool escaped = false;

    for (int i = 0; i < (int)txt.size(); i += 1) {
        if (not escaped and txt[i] == '\\') {
            escaped = true;
            continue;
        }

        if (escaped) {
            if (not NeedsEscape(txt[i])) {
                current_txt += '\\';
            }
            current_txt += txt[i];
            escaped = false;
            continue;
        }

        if (quotes) {
            if (txt[i] == quote_char) {
                quotes = false;
            } else {
                current_txt += txt[i];
            }
            continue;
        }

        if (txt[i] == '\'' or txt[i] == '\"') {
            quotes = true;
            quote_char = txt[i];
            was_quoted = true;
        } else if (IsWhitespace(txt[i])) {
            if (current_txt.size() || was_quoted) {
                output.push_back(current_txt);
            }

            was_quoted = false;
            current_txt = "";
        } else {
            current_txt += txt[i];
        }
    }

    if (current_txt.size() || was_quoted) {
        output.push_back(current_txt);
    }

    return output;
}

char** StringToCharSS(const std::vector<std::string>& splits) {
    char** args = (char**)malloc((splits.size() + 1) * sizeof(char*));
    for (int i = 0; i < (int)splits.size(); i += 1) {
        args[i] = strdup(splits[i].c_str());
    }

    args[(int)splits.size()] = nullptr;
    return args;
}

std::string EscapeString(const std::string& content) {
    std::string result = "";
    for (char itr : content) {
        bool needs_escape = false;
        for (char c : "\"\'\\") {
            if (itr == c) {
                needs_escape = true;
            }
        }

        if (needs_escape) {
            result += '\\';
            result += itr;
            continue;
        }

        if (itr == '\n') {
            result += "\\n";
            continue;
        }

        if (itr == '\r') {
            result += "\\r";
            continue;
        }

        if (itr == '\t') {
            result += "\\t";
            continue;
        }

        result += itr;
    }
    return result;
}

std::string ReadFromFile(const std::string& path) {
    std::ifstream fin(path, std::ios::in | std::ios::binary);
    std::string file_information;

    if (fin) {
        fin.seekg(0, fin.end);
        file_information.resize(fin.tellg());

        fin.seekg(0, fin.beg);

        fin.read(&file_information[0], file_information.size());
        fin.close();
    } else {
        return "";
    }

    return file_information;
}

};  /// namespace Base
