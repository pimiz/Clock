#include "ClockApplicationPrivate.h"
#include "ClockException.h"

// static member initialization
int ClockApplication::Private::currentHours;
int ClockApplication::Private::currentMinutes;

void ClockApplication::Private::adjustClock(const int hours, const int minutes)
{
    std::cout << hours << " " << minutes << std::endl;

    if (hours < 0 || hours > 24)
    {
        // invalid hours
        throw ClockException(std::string("Invalid hours: ") + std::to_string(hours));
    }

    if (minutes < 0 || minutes >= 60)
    {
        // invalid minutes
        throw ClockException(std::string("Invalid minutes: ") + std::to_string(minutes));
    }

    int timeDiff = computeTime(hours, currentHours, minutes, currentMinutes);

    // set hour hand
    setHourHand(timeDiff);
    currentHours = hours;

    // set minute hand
    setMinuteHand(timeDiff);
    currentMinutes = minutes;

    CONSOLE_OUTPUT("Time set to " + std::to_string(currentHours) + ":" + std::to_string(currentMinutes));
 }

void ClockApplication::Private::setHourHand(const int & timeDifference) const
{
    double hourAngleIncrement = static_cast<double>(timeDifference)/60;
    hourAngleIncrement *= 30; // 30 (360/12) degrees equals the angle of a step of an hour
    std::cout << "steps hours " << hourAngleIncrement << std::endl;
    hourHandNode->yaw(-Ogre::Degree(hourAngleIncrement));
}

void ClockApplication::Private::setMinuteHand(const int & timeDifference) const
{
    int minuteAngleIncrement = timeDifference % 60;
    minuteAngleIncrement = minuteAngleIncrement * 6; // 6 (360/60) degrees equals the angle of a step of a minute
    std::cout << "steps minutes " << minuteAngleIncrement << std::endl;
    minuteHandNode->yaw(-Ogre::Degree(minuteAngleIncrement));
}

// Convert time to minutes past midnight
int ClockApplication::Private::convertTimeToMinutes(int hour, int min) const
{
    if (hour == 12)
        hour = 0;
    int calc = hour*60 + min;
    return calc;
}

// Return the absolute time difference from current to target time in minutes
// (how much forward the clock has to be turned)
int ClockApplication::Private::computeTime(int hour1, int hour2, int min1, int min2) const
{
    return convertTimeToMinutes(hour1, min1) -
        convertTimeToMinutes(hour2, min2);
}

// parse user input from websocket and adjust clock accordingly
void ClockApplication::Private::parseAndApplyNewTime(const char * buffer)
{
    char hours[2];
    char minutes[2];
    memcpy(&hours, buffer+1, 2); // bytes 2-3: hours
    memcpy(&minutes, buffer+3, 2); // bytes 4-5: minutes
    adjustClock(atoi(hours), atoi(minutes));
}
