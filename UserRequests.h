#ifndef USERREQUESTS_H
#define USERREQUESTS_H

#include "UserRequest.h"
#include "IClockAdjuster.h"

namespace Clock
{

/* user request for setting time to clock */
class UserRequestSetTime : public UserRequest
{
public:
    UserRequestSetTime(RecvBuffer const & p_buffer);

    ~UserRequestSetTime();

    void process(ClockAdjusterPtr const & p_clockApp) const override;

protected:
    void construct(RecvBuffer const & p_buffer) override;
    int getTimeInMinutesPastMidnight() const;

private:
    /* disable default ctor, copy ctor and assignment operator */
    UserRequestSetTime() = delete;
    UserRequestSetTime(const UserRequestSetTime &) = delete;
    UserRequestSetTime operator=(const UserRequestSetTime &) = delete;

    void setHours(int const p_hours);
    void setMinutes(int const p_minutes);
    int getTimeInMinutesPastMidnight(int const p_hours, int const p_minutes) const;

    /* storable data parsed from user request */
    int m_hours;
    int m_minutes;
};

/* user request for changing colours of clock face and hands */
class UserRequestSetColours : public UserRequest
{
public:
    UserRequestSetColours(RecvBuffer const & p_buffer);

    ~UserRequestSetColours();

    void process(ClockAdjusterPtr const & p_clockApp) const override;

protected:
    void construct(RecvBuffer const & p_buffer) override;

private:
    /* disable default ctor, copy ctor and assignment operator */
    UserRequestSetColours() = delete;
    UserRequestSetColours(const UserRequestSetColours &) = delete;
    UserRequestSetColours operator=(const UserRequestSetColours &) = delete;

    /* storable data parsed from user request */
    std::string m_clockFaceColour;
    std::string m_hourHandColour;
    std::string m_minuteHandColour;
};

}
#endif

