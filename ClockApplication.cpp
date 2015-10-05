#include <sstream>
#include <ctime>
#include <OgreWindowEventUtilities.h>
#include <mutex>
#include "ClockApplication.h"
#include "WebsocketInterface.h"
#include "ClockException.h"
#include "UserRequests.h"

namespace Clock {

ClockApplication::ClockApplication() :
    m_currentHours(0),
    m_currentMinutes(0)
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
    {
        throw ClockException("Setup failed");
        return;
    }

    WebsocketInterface::init();
    WebsocketAmbassador::clearRecvBuffer();

    /* set clock to show current time of system */
    time_t t = time(0);
    struct tm * now = localtime(&t);
    adjustClock(now->tm_hour, now->tm_min);

    /* main event loop starts */
    while(runEventLoop())
    {
        continue;
    }

    // Clean up
    WebsocketInterface::finish();
    destroyScene();
}

bool ClockApplication::runEventLoop()
{
    Ogre::WindowEventUtilities::messagePump();
    if(mWindow->isClosed()) return false;
    if(!mRoot->renderOneFrame()) return false;

    /* check for websocket messages */
    WebsocketInterface::runService();

    /* lock the buffer mutex. when using std::lock_guard the lock
     * gets automatically released when going out of scope */
    MutexGuard lock(WebsocketAmbassador::getMutex());

    if (WebsocketAmbassador::getReceivedBytes() > 0)
    {
        CONSOLE_OUTPUT(WebsocketAmbassador::getReceivedBytes());
        try
        {
            UserRequestPtr request = parseUserRequest(WebsocketAmbassador::getRecvBuffer());

            /* expose only the IClockAdjuster interface from ClockApplication
             * to the user request object -> no need to know the user request type
             * (user given command) in ClockApplication */
            request->process(shared_from_this());
        }
        catch (ClockException &e)
        {
            CONSOLE_OUTPUT_ERROR(e.what());
        }

        WebsocketAmbassador::clearRecvBuffer();
    }

    return true;
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

    /* align camera facing directly the clock */
    mCamera->setPosition(0, clockFaceNode->getPosition().y + 6, 0);
    mCamera->pitch(Ogre::Degree(270));

}

void ClockApplication::adjustClock(int const p_hours, int const p_minutes)
{
    if (p_hours < 0 || p_hours > 24)
    {
        /* invalid hours */
        throw ClockException(std::string("Invalid hours: ") + std::to_string(p_hours));
    }

    if (p_minutes < 0 || p_minutes >= 60)
    {
        /* invalid minutes */
        throw ClockException(std::string("Invalid minutes: ") + std::to_string(p_minutes));
    }

    int timeDiff = computeTimeDifference(p_hours, m_currentHours, p_minutes, m_currentMinutes);

    /* set hour hand */
    setHourHand(timeDiff);
    m_currentHours = p_hours;

    /* set minute hand */
    setMinuteHand(timeDiff);
    m_currentMinutes = p_minutes;

    /* write current time to sending buffer */
    SendBuffer & buf = WebsocketAmbassador::getSendBuffer();
    int currentTime = this->getCurrentTime();
    char timeBuf[sizeof(currentTime)];
    buf[0] = sizeof(currentTime);
    std::string s = std::to_string(currentTime);
    if (sizeof(currentTime) <= SENDBUFFER_SIZE)
    {
        for (int i=0; i < sizeof(currentTime); i++)
        {
            /* 1st byte of buffer reserved to size info */
            buf[i+1] = s[i];
        }
    }

    CONSOLE_OUTPUT("Time set to " + std::to_string(m_currentHours) + ":" + std::to_string(m_currentMinutes));
 }

void ClockApplication::setHourHand(int const & p_timeDifference) const
{
    double hourAngleIncrement = static_cast<double>(p_timeDifference)/60;
    /* 30 (360/12) degrees equals the angle of a step of an hour */
    hourAngleIncrement *= 30;
    hourHandNode->yaw(-Ogre::Degree(hourAngleIncrement));
}

void ClockApplication::setMinuteHand(int const & p_timeDifference) const
{
    int minuteAngleIncrement = p_timeDifference % 60;
    /* 6 (360/60) degrees equals the angle of a step of a minute */
    minuteAngleIncrement = minuteAngleIncrement * 6;
    minuteHandNode->yaw(-Ogre::Degree(minuteAngleIncrement));
}

UserRequestPtr ClockApplication::parseUserRequest(RecvBuffer const & p_buffer)
{
    /* 2nd byte: command */
    char command;
    memcpy(&command, &p_buffer[1], 1);
    UserRequestCommand userReqCom = static_cast<UserRequestCommand>(atoi(&command));
    return createUserRequestObject(userReqCom, p_buffer);
}

/* Convert time to minutes past midnight */
int ClockApplication::convertTimeToMinutes(int const p_hour, int const p_min) const
{
    int hour = p_hour;
    if (hour == 12)
    {
        hour = 0;
    }
    int calc = hour*60 + p_min;
    return calc;
}

/* Return the absolute time difference from current to target time in minutes
 * (how much forward the clock has to be turned) */
int ClockApplication::computeTimeDifference(int const p_hour1, int const p_hour2, int const p_min1, int const p_min2) const
{
    return convertTimeToMinutes(p_hour1, p_min1) -
        convertTimeToMinutes(p_hour2, p_min2);
}

/* Return current time (past midnight) */
int ClockApplication::getCurrentTime()
{
    return convertTimeToMinutes(m_currentHours, m_currentMinutes);
}

}
