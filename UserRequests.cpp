#include <cstring>
#include "UserRequests.h"
#include "ClockException.h"


namespace Clock
{

UserRequestSetTime::UserRequestSetTime(std::array<char, 64> const &buffer) : UserRequest(UserRequestCommand::SET_TIME)
{
    this->construct(buffer);
}

void UserRequestSetTime::construct(std::array<char, 64> const &buffer)
{
    char hours[2];
    char minutes[2];
    memcpy(&hours, &buffer[2], 2); // bytes 3-4: hours
    memcpy(&minutes, &buffer[4], 2); // bytes 5-6: minutes
    m_hours = atoi(hours);
    m_minutes = atoi(minutes);
}

UserRequestSetTime::~UserRequestSetTime()
{
}

void UserRequestSetTime::process(ClockAdjusterPtr const & clockApp) const
{
    clockApp->adjustClock(m_hours, m_minutes);
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


int UserRequestSetTime::getHours() const
{
    return m_hours;
}

int UserRequestSetTime::getMinutes() const
{
    return m_minutes;
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


} // namespace
