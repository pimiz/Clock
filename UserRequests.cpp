#include <cstring>
#include "UserRequests.h"
#include "ClockException.h"


#include <iostream> // DEBUG
#include <regex>

namespace Clock
{
/* Class UserRequestSetTime */
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
    memcpy(&hours, &p_buffer[2], 2); // bytes 3-4: hours
    memcpy(&minutes, &p_buffer[4], 2); // bytes 5-6: minutes
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
/* End class UserRequestSetTime */


/* Class UserRequestSetColours */

UserRequestSetColours::UserRequestSetColours(RecvBuffer const & p_buffer) : UserRequest(UserRequestCommand::SET_COLOURS),
    m_clockFaceColour(""),
    m_hourHandColour(""),
    m_minuteHandColour("")
{
    this->construct(p_buffer);
}

UserRequestSetColours::~UserRequestSetColours()
{

}

void UserRequestSetColours::construct(RecvBuffer const & p_buffer)
{
    /* parse RGBA colour strings from user input.
       check with regex that the strings are in correct format */
    std::string localBuf(std::begin(p_buffer), std::end(p_buffer));
    std::regex regex("[0-9]{2}(#[0-9a-fA-F]{6})(#[0-9a-fA-F]{6})(#[0-9a-fA-F]{6}).*");
    std::smatch matches;

    /* check validity of buffer string format */
    if (!std::regex_match(localBuf, matches, regex))
    {
        throw ClockException(std::string("Could not parse RGBA values: ")+localBuf);
    }

    /* parse RGB values from buffer */
    int iter = 0;

    while (std::regex_search (localBuf, matches, regex)) {
        for (auto match:matches)
        {
            switch (iter)
            {
            /* matches[0] contains the whole regex'd string */
            case 1:
                m_clockFaceColour = match;
                break;
            case 2:
                m_hourHandColour = match;
                break;
            case 3:
                m_minuteHandColour = match;
                break;
            default:
                break;
            }
            iter++;
        }
        localBuf = matches.suffix().str();
    }

}

void UserRequestSetColours::process(ClockAdjusterPtr const & p_clockApp) const
{
    p_clockApp->setClockFaceColour(m_clockFaceColour);
    p_clockApp->setHourHandColour(m_hourHandColour);
    p_clockApp->setMinuteHandColour(m_minuteHandColour);
}
/* End class UserRequestSetColours */
} // namespace
