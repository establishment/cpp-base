#ifndef CPPBASE_RANDOM_HPP
#define CPPBASE_RANDOM_HPP

#include <functional>
#include <vector>

namespace base {

// simple specializations
// return [0, valueMax]
bool RandBool();
bool RandInt1();

char RandInt8();
char RandChar();

short RandShort();
short RandInt16();

int Rand();
int RandInt32();

unsigned RandUInt32();

long RandInt64();

unsigned long RandUInt64();

float RandFloat32();
float RandFloat();

double RandFloat64();
double RandDouble();

// return [0, right)
char RandInt8(char right);
char RandChar(char right);

short RandInt16(short right);
short RandShort(short right);

int Rand(int right);
int RandInt32(int right);

unsigned int RandUInt32(unsigned int right);

long RandInt64(long right);

unsigned long RandUInt64(unsigned long right);

float RandFloat32(float right);

double RandFloat64(double right);

char RandChar(char left, char right);
char RandInt8(char left, char right);

short RandShort(short left, short right);
short RandInt16(short left, short right);

int RandInt(int left, int right);
int RandInt32(int left, int right);

unsigned int RandUInt32(unsigned int left, unsigned int right);

unsigned long RandUInt64(unsigned long left, unsigned long right);

float RandFloat(float left, float right);
float RandFloat32(float left, float right);

double RandDouble(double left, double right);
double RandFloat64(double left, double right);

// returns random numbers from [left, right), number i having the chx = 1/i
template<typename Type>
Type RandLog(Type left, Type right);

template<typename Type>
Type xRandLog(Type left, Type right);

// returns random numbers from [left, right)
// Maps [left, right) to [1, right - left + 1) and calls RandLog
template<typename Type>
Type RandLogScaled(Type left, Type right);

template<typename Type>
Type xRandLogScaled(Type left, Type right);

/**** Unique Numbers ****/
// returns a std::vector containing (numElements) unique numbers from [left, right) which return true for validNumber()
// Complexity
//  Let [good] = number of valid elements from [right, left) and [bad] number of non valid elements from [right, left)
//  Memory O(numElements)
//  Time O(unordered_map_lookup * (good + bad) * (HarmonicNumber(good) - HarmonicNumber(good - numElements))
//  eg: for bad=0, numElements=good / 2 it's ~ O(unordered_map_lookup * numElements * ln(2))
template<typename Type>
std::vector<Type> UniqueNumbers(Type left, Type right, int numElements, const std::function<bool(Type)>& validNumber);

template<typename Type>
std::vector<Type> xUniqueNumbers(Type left, Type right, int numElements, const std::function<bool(Type)>& validNumber);

// returns a std::vector containing (numElements) unique numbers from [0, right) which return true for validNumber()
template<typename Type>
std::vector<Type> UniqueNumbers(Type right, int numElements, const std::function<bool(Type)>& validNumber);

template<typename Type>
std::vector<Type> xUniqueNumbers(Type right, int numElements, const std::function<bool(Type)>& validNumber);

// returns a std::vector containing (numElements) unique numbers from [left, right)
template<typename Type>
std::vector<Type> UniqueNumbers(Type left, Type right, int numElements);

template<typename Type>
std::vector<Type> xUniqueNumbers(Type left, Type right, int numElements);

// returns a std::vector containing (numElements) unique numbers from [0, right)
template<typename Type>
std::vector<Type> UniqueNumbers(Type right, int numElements);

template<typename Type>
std::vector<Type> xUniqueNumbers(Type right, int numElements);

// equivalent to UniqueNumbers(startElement, numElements + startElement);
std::vector<int> RandomPermutation(int numElements, int startElement=0);

/**** Patitioning ****/
// splits [numElements] into [numBuckets]
struct Partition {
    // a random split, from all C(numElements + numBuckets - 1, numBuckets - 1) for minVal = 0
    static std::vector<int> Uniform(int numElements, int numBuckets, int minVal);
};


}  // namespace base

#include "Random.tpp"

#ifndef cppbaseuselib
#include "Random.cpp"
#endif

#endif // CPPBASE_RANDOM_HPP
