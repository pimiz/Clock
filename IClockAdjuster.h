#ifndef ICLOCKADJUSTER_H
#define ICLOCKADJUSTER_H

namespace ClockPublic {

class IClockAdjuster
{
public:
    virtual ~IClockAdjuster() {}
    virtual void adjustClock(int const p_hours, int const p_minutes) = 0;
    virtual void setClockFaceColour(std::string const & clockFaceRGBA) = 0;
    virtual void setHourHandColour(std::string const & hourHandRGBA) = 0;
    virtual void setMinuteHandColour(std::string const & minuteHandRGBA) = 0;
};
}

#endif
