#ifndef CPP_BASE_TIME_HPP
#define CPP_BASE_TIME_HPP

#include <time.h>

namespace base {

// Precise wall time clock
class PreciseTimer {
  public:
    PreciseTimer(clockid_t clockType = CLOCK_REALTIME);

    void start();

    double secElapsed() const;

    double msElapsed() const;

  private:
    clockid_t clockType;
    long long resolution;
    timespec startTime;
};

} // namespace base

#endif // CPP_BASE_TIME_HPP
