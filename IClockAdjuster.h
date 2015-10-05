#ifndef ICLOCKADJUSTER_H
#define ICLOCKADJUSTER_H

namespace ClockPublic {

class IClockAdjuster
{
public:
    virtual ~IClockAdjuster() {}
    virtual void adjustClock(int const p_hours, int const p_minutes) = 0;
};
}

#endif
