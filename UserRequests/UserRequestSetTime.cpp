#ifndef USERREQUESTS_H
#define USERREQUESTS_H

#include <cstring>
#include "UserRequestSetTime.h"
#include "ClockException.h"
#include "IClockAdjuster.h"

namespace Clock
{

UserRequestSetTime::UserRequestSetTime(RecvBuffer const &p_buffer) : UserRequest(UserRequestCommand::SET_TIME),
    m_hours(0),
    m_minutes(0)
{
    this->construct(p_buffer);
}

void UserRequestSetTime::construct(RecvBuffer const &p_buffer)
{
    char hours[2];
    char minutes[2];
    memcpy(&hours, &p_buffer[3], 2); // bytes 4-5: hours
    memcpy(&minutes, &p_buffer[5], 2); // bytes 6-7: minutes
    m_hours = atoi(hours);
    m_minutes = atoi(minutes);
}

UserRequestSetTime::~UserRequestSetTime()
{
}

void UserRequestSetTime::process(ClockAdjusterPtr const & p_clockApp) const
{
    p_clockApp->adjustClock(m_hours, m_minutes);
}

void UserRequestSetTime::setHours(int const p_hours)
{
    if (p_hours < 0 || p_hours > 23)
    {
        throw ClockException(std::string("Hours out of accepted range: ") + std::to_string(p_hours));
    }

    m_hours = p_hours;
}

void UserRequestSetTime::setMinutes(int const p_minutes)
{
    if (p_minutes < 0 || p_minutes > 59)
    {
        throw ClockException(std::string("Minutes out of accepted range") + std::to_string(p_minutes));
    }

    m_minutes = p_minutes;
}

int UserRequestSetTime::getTimeInMinutesPastMidnight() const
{
    return getTimeInMinutesPastMidnight(m_hours, m_minutes);
}

int UserRequestSetTime::getTimeInMinutesPastMidnight(int const p_hours, int const p_minutes) const
{
    int calc = p_hours*60 + p_minutes;
    return calc;
}

}
#endif

