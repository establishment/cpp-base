#include "RandGenFast.hpp"

namespace base {

RandGenFast::RandGenFast() : x(3369674297), y(1430037335), z(3845079233) {
}

RandGenFast::RandGenFast(unsigned int x, unsigned int y, unsigned int z) : x(x), y(y), z(z) {
}

unsigned RandGenFast::uint32() {
    unsigned int t = this->x ^ (this->x << 11);
    this->x = this->y;
    this->y = this->z;
    this->z ^= (this->z >> 19) ^ t ^ (t >> 8);
    return this->z;
}

float RandGenFast::float32() {
    static const double kRandMaxInclusive = 4294967296.0;
    return this->uint32() / kRandMaxInclusive;
}

double RandGenFast::float64() {
    static const double kRandMaxInclusive = 4294967296.0;
    static const double kRandMaxInclusiveSquared = 18446744073709551616.0;
    return (this->uint32() * kRandMaxInclusive + this->uint32()) / kRandMaxInclusiveSquared;
}

bool RandGenFast::int1() {
    return this->uint32() & 1;
}

char RandGenFast::int8() {
    return this->uint32() & 127;
}

short RandGenFast::int16() {
    return this->uint32() & 32767;
}

int RandGenFast::int32() {
    return this->uint32() & 2147483647;
}

long RandGenFast::int64() {
    return (long(this->int32()) << 32) | this->uint32();
}

unsigned long RandGenFast::uint64() {
    return ((unsigned long)(this->uint32()) << 32) | this->uint32();
}

char RandGenFast::int8(char right) {
    return this->uint32() % right;
}

short RandGenFast::int16(short right) {
    return this->uint32() % right;
}

int RandGenFast::int32(int right) {
    return this->uint32() % right;
}

unsigned int RandGenFast::uint32(unsigned int right) {
    return this->uint32() % right;
}

long RandGenFast::int64(long right) {
    return this->uint64() % right;
}

unsigned long RandGenFast::uint64(unsigned long right) {
    return this->uint64() % right;
}

float RandGenFast::float32(float right) {
	return this->float32() * right;
}

double RandGenFast::float64(double right) {
	return this->float64() * right;
}

char RandGenFast::int8(char left, char right) {
    return left + this->uint32() % (right - left);
}

short RandGenFast::int16(short left, short right) {
    return left + this->uint32() % (right - left);
}

int RandGenFast::int32(int left, int right) {
    return (long)left + this->uint64() % (right - left);
}

unsigned int RandGenFast::uint32(unsigned int left, unsigned int right) {
    return left + this->uint32() % (right - left);
}

unsigned long RandGenFast::uint64(unsigned long left, unsigned long right) {
    return left + this->uint64() % (right - left);
}

float RandGenFast::float32(float left, float right) {
    return left + this->float32() * (right - left);
}

double RandGenFast::float64(double left, double right) {
    return left + this->float64() * (right - left);
}

}; // namespace base
