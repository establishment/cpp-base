#include <iostream>

#include <cassert>

#include <algorithm>
#include <functional>
#include <unordered_map>
#include <vector>

namespace Base {

// Random utils
template <>
int Rand<int>() {
    return rand();
};

template <>
long long Rand<long long>() {
    return 1LL * rand() * RAND_MAX + rand();
};

template <typename Type>
Type Rand(Type right) {
    return Rand<Type>(static_cast<Type>(0), right);
}

template <typename Type>
Type xRand(Type right) {
    return Rand<Type>(static_cast<Type>(0), right + static_cast<Type>(1));
}

template <>
int Rand<int>(int left, int right) {
    if (left == right) {
        return 0;
    }
    long long x = 1LL * rand() * RAND_MAX + rand();
    x %= (long long)right - left;
    x += left;
    return x;
};

template <>
int xRand<int>(int left, int right) {
    return Rand(left, right + 1);
}

template <>
long long Rand<long long>(long long left, long long right) {
    if (left == right) {
        return 0;
    }
    long long x = 1LL * rand() * RAND_MAX + rand();
    x %= (right - left);
    x += left;
    return x;
}

template <>
long long xRand<long long>(long long left, long long right) {
    return Rand(left, right + 1);
}

template <>
double Rand<double>(double left, double right) {
    long double x = (1.0 * rand() * RAND_MAX + rand()) / RAND_MAX / RAND_MAX;
    x *= (right - left);
    x += left;
    return (double)x;
}

template <>
long double Rand<long double>(long double left, long double right) {
    long double x = (1.0 * rand() * RAND_MAX + rand()) / RAND_MAX / RAND_MAX;
    x *= (right - left);
    x += left;
    return x;
}

template <typename Type>
Type RandLog(Type left, Type right) {
    long double x = Rand<long double>(std::log2(left), std::log2(right));
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
std::vector<Type> UniqueNumbers(Type left, Type right, int num_elements,
                                const std::function<bool(Type)>& valid_number) {
    assert(right - left >= num_elements);
    assert(left <= right);

    std::unordered_map<Type, bool> selected_numbers;

    std::vector<Type> result;
    result.reserve(num_elements);

    while (num_elements > 0) {
        int element = std::rand() % (right - left) + left;
        if (not selected_numbers[element] and valid_number(element)) {
            selected_numbers[element] = true;
            result.push_back(element);
            num_elements -= 1;
        }
    }

    return result;
};

template <typename Type>
std::vector<Type> xUniqueNumbers(Type left, Type right, int num_elements,
                                 const std::function<bool(Type)>& valid_number) {
    return UniqueNumbers(left, right + 1, num_elements, valid_number);
};

template <typename Type>
std::vector<Type> UniqueNumbers(Type right, int num_elements, const std::function<bool(Type)>& valid_number) {
    return UniqueNumbers<Type>((Type)0, right, num_elements, valid_number);
};

template <typename Type>
std::vector<Type> xUniqueNumbers(Type right, int num_elements, const std::function<bool(Type)>& valid_number) {
    return UniqueNumbers<Type>((Type)0, right + (Type)1, num_elements, valid_number);
};

template <typename Type>
std::vector<Type> UniqueNumbers(Type left, Type right, int num_elements) {
    return UniqueNumbers<Type>(left, right, num_elements, [](Type) -> bool { return true; });
};

template <typename Type>
std::vector<Type> xUniqueNumbers(Type left, Type right, int num_elements) {
    return UniqueNumbers<Type>(left, right + (Type)1, num_elements, [](Type) -> bool { return true; });
};

template <typename Type>
std::vector<Type> UniqueNumbers(Type right, int num_elements) {
    return UniqueNumbers<Type>((Type)0, right, num_elements, [](Type) -> bool { return true; });
};

template <typename Type>
std::vector<Type> xUniqueNumbers(Type right, int num_elements) {
    return UniqueNumbers<Type>((Type)0, right + (Type)1, num_elements, [](Type) -> bool { return true; });
};

}  // namespace Base
