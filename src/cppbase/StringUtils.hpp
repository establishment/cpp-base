#ifndef CPPBASE_STRING_UTILS_HPP
#define CPPBASE_STRING_UTILS_HPP

#include <string>
#include <vector>

// add new functionality to std::to_string
namespace std {
std::string to_string(const std::string& t);

std::string to_string(const char& c);

std::string to_string(const char* t);
};  //  namespace std

namespace base {
// optimise for multime recursive calls to StrCat if used like to_string(T) + StrCat(args...)
// last element is apended n - 1 time
template <typename T>
void StrCatHelper(std::string& targetResult, const T t);

template <typename T, typename... Args>
void StrCatHelper(std::string& targetResult, const T t, const Args... args);

// Concatenates all args into a big string, calling to_string on them
// see to_string added functionality above
template <typename T>
std::string StrCat(const T t);

template <typename T, typename... Args>
std::string StrCat(const T t, const Args... args);

bool NeedsEscape(char c);

bool IsWhitespace(char c);

std::vector<std::string> ParseCommandLine(const std::string& txt);

char** StringToCharSS(const std::vector<std::string>& splits);

std::string EscapeString(const std::string& content);

std::string ReadFromFile(const std::string& path);

};  // namespace base

#include "StringUtils.tpp"

#ifndef cppbaseuselib
#include "StringUtils.cpp"
#endif

#endif // CPPBASE_STRING_UTILS_HPP
