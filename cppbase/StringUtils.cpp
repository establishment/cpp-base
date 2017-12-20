#include "StringUtils.hpp"

#include <string.h>
#include <fstream>
#include <string>
#include <vector>

namespace base {
bool NeedsEscape(char c) {
    static std::string escapedCharacters = " \n\t\r\f\"\'";
    for (char itr : escapedCharacters) {
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
    std::string currentTxt = "";
    std::vector<std::string> output;
    bool quotes = false;
    bool wasQuoted = false;
    char quoteChar = '\0';
    bool escaped = false;

    for (int i = 0; i < (int)txt.size(); i += 1) {
        if (not escaped and txt[i] == '\\') {
            escaped = true;
            continue;
        }

        if (escaped) {
            if (not NeedsEscape(txt[i])) {
                currentTxt += '\\';
            }
            currentTxt += txt[i];
            escaped = false;
            continue;
        }

        if (quotes) {
            if (txt[i] == quoteChar) {
                quotes = false;
            } else {
                currentTxt += txt[i];
            }
            continue;
        }

        if (txt[i] == '\'' or txt[i] == '\"') {
            quotes = true;
            quoteChar = txt[i];
            wasQuoted = true;
        } else if (IsWhitespace(txt[i])) {
            if (currentTxt.size() || wasQuoted) {
                output.push_back(currentTxt);
            }

            wasQuoted = false;
            currentTxt = "";
        } else {
            currentTxt += txt[i];
        }
    }

    if (currentTxt.size() || wasQuoted) {
        output.push_back(currentTxt);
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
        bool needsEscape = false;
        for (char c : "\"\'\\") {
            if (itr == c) {
                needsEscape = true;
            }
        }

        if (needsEscape) {
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
    std::string fileInformation;

    if (fin) {
        fin.seekg(0, fin.end);
        fileInformation.resize(fin.tellg());

        fin.seekg(0, fin.beg);

        fin.read(&fileInformation[0], fileInformation.size());
        fin.close();
    } else {
        return "";
    }

    return fileInformation;
}

};  /// namespace base
