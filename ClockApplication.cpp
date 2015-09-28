#include <sstream>
#include <ctime>
#include <OgreWindowEventUtilities.h>
#include "ClockApplication.h"
#include "ClockApplicationPrivate.h"
#include "WebsocketInterface.h"
#include "WebsocketAmbassador.h"
#include "ClockException.h"


ClockApplication::Private * ClockApplication::d;


ClockApplication::ClockApplication()
{
    d = new Private();
    d->currentHours = 0;
    d->currentMinutes = 0;
}

ClockApplication::~ClockApplication(void)
{
    delete d;
}

void ClockApplication::go(void)
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

    if (!setup())
        return;

    // initialize websocket ambassador to receive and send messages from websocket interface
    WebsocketAmbassador &amb = WebsocketAmbassador::getInstance();

    // set clock to show current time of system
    time_t t = time(0);
    struct tm * now = localtime(&t);
    d->adjustClock(now->tm_hour, now->tm_min);

    // main event loop
    while(true)
    {
      Ogre::WindowEventUtilities::messagePump();

      if(mWindow->isClosed()) break; // false;

      if(!mRoot->renderOneFrame()) break; // false;

      // check for websocket messages
      WebsocketInterface::runService();

      if (amb.getRecvBufferSize() > 0)
      {
        try
        {
            processUserRequest(amb.getRecvBuffer());
        }
        catch (ClockException &e)
        {
            CONSOLE_OUTPUT_ERROR(e.what());
        }

        amb.clearBuffer();
      }

      CONSOLE_OUTPUT(mCamera->getDirection());
    }

    // Clean up
    destroyScene();
}

void ClockApplication::createScene(void)
{
    mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0, 1.0, 1.0));

    d->hourHand = mSceneMgr->createEntity("HourHand", "HourHand.mesh");
    d->minuteHand = mSceneMgr->createEntity("MinuteHand", "MinuteHand.mesh");
    d->clockFace = mSceneMgr->createEntity("clockFace", "ClockFace.mesh");
    d->hourHandNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("HourHandNode");
    d->minuteHandNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("MinuteHandNode");
    d->clockFaceNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("ClockFaceNode");
    d->hourHandNode->attachObject(d->hourHand);
    d->minuteHandNode->attachObject(d->minuteHand);
    d->clockFaceNode->attachObject(d->clockFace);

    // align camera directly on clock
    mCamera->setPosition(0, d->clockFaceNode->getPosition().y + 6, 0);
    mCamera->pitch(Ogre::Degree(270));

}

void ClockApplication::processUserRequest(char * buffer)
{
    // 1st byte: command

    char command;
    memcpy(&command, buffer, 1);

    switch (atoi(&command))
    {
        case 1: // adjust time
        {
            d->parseAndApplyNewTime(buffer);
            break;
        }
        case 2:
        {

        }
        default:
            break;
    }
}

// return current time (past midnight)
int ClockApplication::getCurrentTime()
{
    return d->convertTimeToMinutes(d->currentHours, d->currentMinutes);
}

