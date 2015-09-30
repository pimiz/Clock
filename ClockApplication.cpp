#include <sstream>
#include <ctime>
#include <OgreWindowEventUtilities.h>
#include "ClockApplication.h"
#include "WebsocketInterface.h"
#include "ClockException.h"
#include "UserRequests.h"

namespace Clock {


ClockApplication::ClockApplication() :
    currentHours(0),
    currentMinutes(0)
{

#ifdef _DEBUG
#ifndef OGRE_STATIC_LIB
    mResourcesCfg = m_ResourcePath + "resources_d.cfg";
    mPluginsCfg = m_ResourcePath + "plugins_d.cfg";
#else
    mResourcesCfg = "resources_d.cfg";
    mPluginsCfg = "plugins_d.cfg";
#endif
#else
#ifndef OGRE_STATIC_LIB
    mResourcesCfg = m_ResourcePath + "resources.cfg";
    mPluginsCfg = m_ResourcePath + "plugins.cfg";
#else
    mResourcesCfg = "resources.cfg";
    mPluginsCfg = "plugins.cfg";
#endif
#endif


}

ClockApplication::~ClockApplication()
{
}

void ClockApplication::go()
{
    if (!setup())
        throw ClockException("Setup failed");
        //return;

    // set clock to show current time of system
    time_t t = time(0);
    struct tm * now = localtime(&t);
    adjustClock(now->tm_hour, now->tm_min);


    WebsocketAmbassador::clearRecvBuffer();

    // main event loop
    while(true)
    {
      Ogre::WindowEventUtilities::messagePump();

      if(mWindow->isClosed()) break; // false;

      if(!mRoot->renderOneFrame()) break; // false;

      // check for websocket messages
      WebsocketInterface::runService();

      WebsocketAmbassador::getMutex().lock();
      if (WebsocketAmbassador::getReceivedBytes() > 0)
      {
          CONSOLE_OUTPUT(WebsocketAmbassador::getReceivedBytes());
        try
        {
            IUserRequest * request = parseUserRequest(WebsocketAmbassador::getRecvBuffer());
            processUserRequest(request);
            delete request;
        }
        catch (ClockException &e)
        {
            CONSOLE_OUTPUT_ERROR(e.what());
        }

        WebsocketAmbassador::clearRecvBuffer();
      }
      WebsocketAmbassador::getMutex().unlock();
    }

    // Clean up
    destroyScene();
}

void ClockApplication::createScene()
{
    mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0, 1.0, 1.0));

    hourHand = mSceneMgr->createEntity("HourHand", "HourHand.mesh");
    minuteHand = mSceneMgr->createEntity("MinuteHand", "MinuteHand.mesh");
    clockFace = mSceneMgr->createEntity("clockFace", "ClockFace.mesh");
    hourHandNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("HourHandNode");
    minuteHandNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("MinuteHandNode");
    clockFaceNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("ClockFaceNode");
    hourHandNode->attachObject(hourHand);
    minuteHandNode->attachObject(minuteHand);
    clockFaceNode->attachObject(clockFace);

    // align camera directly on clock
    mCamera->setPosition(0, clockFaceNode->getPosition().y + 6, 0);
    mCamera->pitch(Ogre::Degree(270));

}

void ClockApplication::processUserRequest(IUserRequest * p_request)
{
    // 1st byte: command

    switch (p_request->getCommand())
    {
    case UserRequestCommand::SET_TIME: // adjust time
    {
        const UserRequestSetTime * setTime = dynamic_cast<const UserRequestSetTime *>(p_request);
        adjustClock(setTime->getHours(), setTime->getMinutes());
        break;
    }
    case UserRequestCommand::CHANGE_COLOR:
    {
        // TODO implement
    }
    default:
        break;
    }
}

void ClockApplication::adjustClock(const int hours, const int minutes)
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

void ClockApplication::setHourHand(const int & timeDifference) const
{
    double hourAngleIncrement = static_cast<double>(timeDifference)/60;
    hourAngleIncrement *= 30; // 30 (360/12) degrees equals the angle of a step of an hour
    std::cout << "steps hours " << hourAngleIncrement << std::endl;
    hourHandNode->yaw(-Ogre::Degree(hourAngleIncrement));
}

void ClockApplication::setMinuteHand(const int & timeDifference) const
{
    int minuteAngleIncrement = timeDifference % 60;
    minuteAngleIncrement = minuteAngleIncrement * 6; // 6 (360/60) degrees equals the angle of a step of a minute
    std::cout << "steps minutes " << minuteAngleIncrement << std::endl;
    minuteHandNode->yaw(-Ogre::Degree(minuteAngleIncrement));
}

// Convert time to minutes past midnight
// TODO remove this from here
int ClockApplication::convertTimeToMinutes(int hour, int min) const
{
    if (hour == 12)
        hour = 0;
    int calc = hour*60 + min;
    return calc;
}

// Return the absolute time difference from current to target time in minutes
// (how much forward the clock has to be turned)
// TODO transfer to UserRequestSetTime class
int ClockApplication::computeTime(int hour1, int hour2, int min1, int min2) const
{
    return convertTimeToMinutes(hour1, min1) -
        convertTimeToMinutes(hour2, min2);
}


// return current time (past midnight)
int ClockApplication::getCurrentTime()
{
    return convertTimeToMinutes(currentHours, currentMinutes);
}

IUserRequest * ClockApplication::parseUserRequest(recvBuffer &buffer)
{
    // 2nd byte: command
    char command;
    memcpy(&command, &buffer[1], 1);

    UserRequestCommand urq = static_cast<UserRequestCommand>(atoi(&command));


    switch (urq)
    {
    case UserRequestCommand::SET_TIME: // set time
    {
        UserRequestSetTime * setTime = new UserRequestSetTime();

        char hours[2];
        char minutes[2];
        memcpy(&hours, &buffer[2], 2); // bytes 3-4: hours
        memcpy(&minutes, &buffer[4], 2); // bytes 5-6: minutes
        setTime->setHours(atoi(hours));
        setTime->setMinutes(atoi(minutes));
        return setTime;
        break;
    }
    case UserRequestCommand::CHANGE_COLOR: // change color of clock
    {
        // TODO implement
    }
    default:
        throw ClockException("Unknown user request command");
        break;
    }

    return nullptr;

}

}
