#ifndef CLOCKAPPLICATIONPRIVATE_H
#define CLOCKAPPLICATIONPRIVATE_H

#include "ClockApplication.h"

/* Actual implementation of ClockApplication class */

class ClockApplication::Private
{
public:
    void adjustClock(const int hours, const int minutes);
    void setHourHand(const int & timeDifference) const;
    void setMinuteHand(const int & timeDifference) const;

    // Convert time to minutes past midnight
    int convertTimeToMinutes(int hour, int min) const;

    // Return the absolute time difference from current to target time in minutes
    // (how much forward the clock has to be turned)
    int computeTime(int hour1, int hour2, int min1, int min2) const;

    // parse user input from websocket and adjust clock accordingly
    void parseAndApplyNewTime(const char * buffer);

    Ogre::Entity* hourHand;
    Ogre::Entity* minuteHand;
    Ogre::Entity* clockFace;
    Ogre::SceneNode* hourHandNode;
    Ogre::SceneNode* minuteHandNode;
    Ogre::SceneNode* clockFaceNode;
    static int currentHours;
    static int currentMinutes;
};

#endif
