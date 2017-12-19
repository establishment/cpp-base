#include <cassert>
#include <cmath>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <vector>

#include "RandGenFast.hpp"

namespace base {

template <typename Type>
Type RandLog(Type left, Type right) {
    double x = RandFloat64(std::log2(left), std::log2(right));
    Type r = std::pow(2.0, x);
    assert(left <= r);
    assert(r < right);
    return r;
}

template <typename Type>
Type xRandLog(Type left, Type right) {
    return RandLog(left, right + (Type)1);
}

template <typename Type>
Type RandLogScaled(Type left, Type right) {
    return RandLog<Type>((Type)1, right - left + (Type)1) + (left - 1);
}

template <typename Type>
Type xRandLogScaled(Type left, Type right) {
    return RandLog<Type>((Type)1, right - left + (Type)2) + (left - 1);
}

template <typename Type>
std::vector<Type> UniqueNumbers(Type left, Type right, int numElements,
                                const std::function<bool(Type)>& validNumber) {
    assert(right - left >= numElements);
    assert(left <= right);

    std::unordered_map<Type, bool> selectedNumbers;

    std::vector<Type> result;
    result.reserve(numElements);

    while (numElements > 0) {
        int element = std::rand() % (right - left) + left;
        if (not selectedNumbers[element] and validNumber(element)) {
            selectedNumbers[element] = true;
            result.push_back(element);
            numElements -= 1;
        }
    }

    return result;
};

template <typename Type>
std::vector<Type> xUniqueNumbers(Type left, Type right, int numElements,
                                 const std::function<bool(Type)>& validNumber) {
    return UniqueNumbers(left, right + 1, numElements, validNumber);
};

template <typename Type>
std::vector<Type> UniqueNumbers(Type right, int numElements, const std::function<bool(Type)>& validNumber) {
    return UniqueNumbers<Type>((Type)0, right, numElements, validNumber);
};

template <typename Type>
std::vector<Type> xUniqueNumbers(Type right, int numElements, const std::function<bool(Type)>& validNumber) {
    return UniqueNumbers<Type>((Type)0, right + (Type)1, numElements, validNumber);
};

template <typename Type>
std::vector<Type> UniqueNumbers(Type left, Type right, int numElements) {
    return UniqueNumbers<Type>(left, right, numElements, [](Type) -> bool { return true; });
};

template <typename Type>
std::vector<Type> xUniqueNumbers(Type left, Type right, int numElements) {
    return UniqueNumbers<Type>(left, right + (Type)1, numElements, [](Type) -> bool { return true; });
};

template <typename Type>
std::vector<Type> UniqueNumbers(Type right, int numElements) {
    return UniqueNumbers<Type>((Type)0, right, numElements, [](Type) -> bool { return true; });
};

template <typename Type>
std::vector<Type> xUniqueNumbers(Type right, int numElements) {
    return UniqueNumbers<Type>((Type)0, right + (Type)1, numElements, [](Type) -> bool { return true; });
};

}  // namespace base
