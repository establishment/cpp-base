#ifndef CPP_BASE_DEBUG_HPP
#define CPP_BASE_DEBUG_HPP

#include <ostream>
#include <map>
#include <vector>

#define Debug(...) base::DebugSplitPrint(#__VA_ARGS__, __VA_ARGS__)

namespace base {

template <typename T, typename T2>
std::ostream& operator<<(std::ostream& out, const std::map<T, T2>& rhs);

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& rhs);

void DebugPrint(const char*& allNames, const char* value);

template <typename T>
void DebugPrint(const char*& allNames, T value);

template <typename T>
void DebugSplitPrintHelper(const char*& allNames, T value);

template <typename T, typename... Args>
void DebugSplitPrintHelper(const char*& allNames, T value, Args... args);

template <typename... Args>
void DebugSplitPrint(const char* allNames, Args... args);

} // namespace base

#include "Debug.tpp"

#endif // CPP_BASE_DEBUG_HPP
