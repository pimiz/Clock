#ifndef USERREQUESTSETTIME_H
#define USERREQUESTSETTIME_H

#include "UserRequest.h"

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

}
#endif

