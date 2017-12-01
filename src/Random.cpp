#include "Random.hpp"

#include <algorithm>

#include "Utils.hpp"

namespace base {

RandGenFast rng;

bool RandBool() { return rng.int1(); }

bool RandInt1() { return rng.int1(); }

char RandInt8() { return rng.int8(); }
char RandChar() { return rng.int8(); }

short RandShort() { return rng.int16(); }
short RandInt16() { return rng.int16(); }

int Rand() { return rng.int32(); }
int RandInt32() { return rng.int32(); }

unsigned RandUInt32() { return rng.uint32(); }

long RandInt64() { return rng.int64(); }

unsigned long RandUInt64() { return rng.uint64(); }

float RandFloat32() { return rng.float32(); }
float RandFloat() { return rng.float32(); }

double RandFloat64() { return rng.float64(); }
double RandDouble() { return rng.float64(); }

// return [0, right)
char RandInt8(char right) { return rng.int8(right); }
char RandChar(char right) { return rng.int8(right); }

short RandInt16(short right) { return rng.int16(right); }
short RandShort(short right) { return rng.int16(right); }

int Rand(int right) { return rng.int32(right); }
int RandInt32(int right) { return rng.int32(right); }

unsigned int RandUInt32(unsigned int right) { return rng.uint32(right); }

long RandInt64(long right) { return rng.int64(right); }

unsigned long RandUInt64(unsigned long right) { return rng.uint64(right); }

float RandFloat32(float right) { return rng.float32(right); }

double RandFloat64(double right) { return rng.float64(right); }


char RandChar(char left, char right) { return rng.int8(left, right); }
char RandInt8(char left, char right) { return rng.int8(left, right); }

short RandShort(short left, short right) { return rng.int16(left, right); }
short RandInt16(short left, short right){ return rng.int16(left, right); }

int RandInt(int left, int right) { return rng.int32(left, right); }
int RandInt32(int left, int right) { return rng.int32(left, right); }

unsigned int RandUInt32(unsigned int left, unsigned int right) { return rng.uint32(left, right); } 

unsigned long RandUInt64(unsigned long left, unsigned long right) { return rng.uint64(left, right); } 

float RandFloat(float left, float right) { return rng.float32(left, right); } 
float RandFloat32(float left, float right) { return rng.float32(left, right); }

double RandDouble(double left, double right) { return rng.float64(left, right); }
double RandFloat64(double left, double right) { return rng.float64(left, right); }

std::vector<int> Partition::Uniform(int numElements, int numBuckets, int minVal) {
    numElements -= numBuckets * minVal;

    std::vector<int> delimiters = UniqueNumbers((int)0, numElements + numBuckets - 1, numBuckets - 1);

    std::sort(delimiters.begin(), delimiters.end());

    delimiters.push_back(numElements + numBuckets - 1);

    delimiters.insert(delimiters.begin(), -1);

    std::vector<int> sizes;

    for (int i = 1; i <= numBuckets; i += 1) {
        sizes.push_back(delimiters[i] - delimiters[i - 1] - 1 + minVal);
    }

    return sizes;
};

std::vector<int> RandomPermutation(int numElements, int startElement) {
    std::vector<int> permutation(numElements);
    int sum = startElement;

    for (auto& itr : permutation) {
        itr = sum;
        sum += 1;
    }

    RandomShuffle(permutation);
    return permutation;
}

}  // namespace base
