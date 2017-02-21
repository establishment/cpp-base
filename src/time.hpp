#ifndef BASE_TIME
#define BASE_TIME


#include <time.h>

/// Precise wall time clock
struct PreciseTimer {
    PreciseTimer(int clockType = CLOCK_REALTIME) {
        this->clockType = clockType;
        timespec res;
        clock_getres(clockType, &res);
        resolution = res.tv_sec * 1000000000ll + res.tv_nsec;
        start();
    }

    int clockType;
    long long resolution;
    timespec start_time;

    void start() {
        clock_gettime(clockType, &start_time);
    }

    double secElapsed() const {
        timespec temp;
        clock_gettime(clockType, &temp);

        int difSec = temp.tv_sec - start_time.tv_sec;
        int difNS = (int)temp.tv_nsec - (int)start_time.tv_nsec;

        return difSec + difNS / 1e9;
    }

    double msElapsed() const {
        return secElapsed() * 1000.0;
    }
};

#endif
