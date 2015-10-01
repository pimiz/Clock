#include <cstring>
#include "UserRequests.h"
#include "ClockException.h"


namespace Clock
{
UserRequestSetTime::UserRequestSetTime() : IUserRequest(UserRequestCommand::SET_TIME),
    hours_(0), minutes_(0)
{
}


UserRequestSetTime::UserRequestSetTime(std::array<char, 64> const &buffer) : IUserRequest(UserRequestCommand::SET_TIME)
{
  this->construct(buffer);
}

void UserRequestSetTime::construct(std::array<char, 64> const &buffer)
{
    char hours[2];
    char minutes[2];
    memcpy(&hours, &buffer[2], 2); // bytes 3-4: hours
    memcpy(&minutes, &buffer[4], 2); // bytes 5-6: minutes
    hours_ = atoi(hours);
    minutes_ = atoi(minutes);
}

UserRequestSetTime::~UserRequestSetTime()
{
}

void UserRequestSetTime::setHours(const int p_hours)
{
    if (p_hours < 0 || p_hours > 23)
    {
        throw ClockException("Hours out of accepted range");
    }

    /* We use 12h time format inside this application */
    if (p_hours >= 12)
    {
        hours_ = p_hours - 12;
    }
    else
    {
        hours_ = p_hours;
    }
}

void UserRequestSetTime::setMinutes(const int p_minutes)
{
    if (p_minutes < 0 || p_minutes > 59)
    {
        throw ClockException("Minutes out of accepted range");
    }

    minutes_ = p_minutes;
}


int UserRequestSetTime::getHours() const
{
    return hours_;
}

int UserRequestSetTime::getMinutes() const
{
    return minutes_;
}

int UserRequestSetTime::getTimeInMinutesPastZero() const
{
    return getTimeInMinutesPastZero(hours_, minutes_);
}

int UserRequestSetTime::getTimeInMinutesPastZero(const int p_hours, const int p_minutes) const
{
    int calc = p_hours*60 + p_minutes;
    return calc;
}

} // namespace
