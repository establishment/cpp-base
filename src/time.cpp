#include "time.hpp"

PreciseTimer::PreciseTimer(clockid_t clock_type) {
    this->clock_type = clock_type;
    timespec res;
    clock_getres(clock_type, &res);
    resolution = res.tv_sec * 1000000000ll + res.tv_nsec;
    Start();
}

void PreciseTimer::Start() {
    clock_gettime(clock_type, &start_time);
}

double PreciseTimer::SecElapsed() const {
    timespec temp;
    clock_gettime(clock_type, &temp);

    int difSec = temp.tv_sec - start_time.tv_sec;
    int difNS = (int)temp.tv_nsec - (int)start_time.tv_nsec;

    return difSec + difNS / 1e9;
}

double PreciseTimer::MsElapsed() const {
    return SecElapsed() * 1000.0;
}
