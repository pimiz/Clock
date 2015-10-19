#ifndef USERREQUESTS_H
#define USERREQUESTS_H

#include <regex>
#include "UserRequestSetColours.h"
#include "ClockException.h"
#include "IClockAdjuster.h"

namespace Clock
{

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
    std::regex regex("[0-9]{3}(#[0-9a-fA-F]{6})(#[0-9a-fA-F]{6})(#[0-9a-fA-F]{6}).*");
    std::smatch matches;

    /* check validity of buffer string format */
    if (!std::regex_match(localBuf, matches, regex))
    {
        throw ClockException(std::string("Could not parse RGB values: ")+localBuf);
    }

    /* parse RGB values from buffer */
    int iter = 0;

    while (std::regex_search(localBuf, matches, regex)) {
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

}
#endif

