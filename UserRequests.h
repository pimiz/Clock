#ifndef USERREQUESTS_H
#define USERREQUESTS_H

#include "UserRequest.h"
#include "IClockAdjuster.h"

namespace Clock
{

class UserRequestSetTime : public UserRequest
{
public:
    UserRequestSetTime(RecvBuffer const & p_buffer);

    ~UserRequestSetTime();

    int getHours() const;

    int getMinutes() const;

    int getTimeInMinutesPastMidnight() const;

    void process(ClockAdjusterPtr const & clockApp) const override;

protected:
    void construct(RecvBuffer const & p_buffer) override;

private:
    /* disable default constructor */
    UserRequestSetTime() = delete;
    UserRequestSetTime(const UserRequestSetTime&) = delete;
    UserRequestSetTime operator=(const UserRequestSetTime &) = delete;
    void setHours(int const p_hours);
    void setMinutes(int const p_minutes);
    int getTimeInMinutesPastMidnight(int const p_hours, int const p_minutes) const;

    int m_hours;
    int m_minutes;
};

}

#endif

