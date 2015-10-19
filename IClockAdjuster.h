/* IClockAdjuster.h - header for IClockAdjuster
 * --------------------------------------------
 * IClockAdjuster is an interface class which
 * has to be implemented by clock application to
 * provide functionality for adjusting time and
 * colours of the clock. A user request object invokes
 * this interface so the whole implementation of
 * clock application does not have to be exposed. */

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
