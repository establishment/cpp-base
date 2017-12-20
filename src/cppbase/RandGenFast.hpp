#ifndef CPPBASE_RAND_GEN_FAST_HPP
#define CPPBASE_RAND_GEN_FAST_HPP

namespace base {

class RandGenFast {
  protected:
    unsigned int x, y, z;

  public:
    static const unsigned int kRandMax = -1;

    RandGenFast();

    RandGenFast(unsigned int x, unsigned int y, unsigned int z);

    // primitives
    unsigned uint32();

    float float32();

    double float64();

    // simple specializations
    // return [0, valueMax]
    bool int1();

    char int8();

    short int16();

    int int32();

    long int64();

    unsigned long uint64();

    // return [0, right)
    char int8(char right);

    short int16(short right);

    int int32(int right);

    unsigned int uint32(unsigned int right);

    long int64(long right);

    unsigned long uint64(unsigned long right);

    float float32(float right);

    double float64(double right);

    char int8(char left, char right);

    short int16(short left, short right);

    int int32(int left, int right);

    unsigned int uint32(unsigned int left, unsigned int right);

    unsigned long uint64(unsigned long left, unsigned long right);

    float float32(float left, float right);

    double float64(double left, double right);
};

}; // namespace base

#ifndef cppbaseuselib
#include "RandGenFast.cpp"
#endif

#endif
