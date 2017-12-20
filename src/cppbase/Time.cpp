#include "Time.hpp"

#include <time.h>

namespace base {

PreciseTimer::PreciseTimer(clockid_t clockType) : clockType(clockType) {
    timespec res;
    clock_getres(clockType, &res);
    this->resolution = res.tv_sec * 1000000000ll + res.tv_nsec;
    this->start();
}

void PreciseTimer::start() {
    clock_gettime(clockType, &(this->startTime));
}

double PreciseTimer::secElapsed() const {
    timespec temp;
    clock_gettime(clockType, &temp);

    int difSec = temp.tv_sec - this->startTime.tv_sec;
    int difNS = (int)temp.tv_nsec - (int)this->startTime.tv_nsec;

    return difSec + difNS / 1e9;
}

double PreciseTimer::msElapsed() const {
    return this->secElapsed() * 1000.0;
}

} // namespace base
