#ifndef CPP_BASE_TIME_HPP
#define CPP_BASE_TIME_HPP

#include <time.h>

// Precise wall time clock
class PreciseTimer {
  public:
    PreciseTimer(clockid_t clock_type = CLOCK_REALTIME);

    void Start();

    double SecElapsed() const;

    double MsElapsed() const;
  private:
    clockid_t clock_type;
    long long resolution;
    timespec start_time;
};

#endif // CPP_BASE_TIME_HPP
