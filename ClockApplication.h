#ifndef CLOCKAPPLICATION_H
#define CLOCKAPPLICATION_H

#include "BufferProvider.h"
#include "IClockApplication.h"
#include "IUserRequest.h"

namespace Clock {

class ClockApplication : public IClockApplication::IClockApplication
{
public:
    ClockApplication();
    ~ClockApplication();
    void go() override;
    void createScene() override;

    /*static*/ int getCurrentTime() override;

protected:

    void processUserRequest(IUserRequest * p_request);
    IUserRequest * parseUserRequest(recvBuffer &buffer);

    void adjustClock(const int hours, const int minutes);
    void setHourHand(const int & timeDifference) const;
    void setMinuteHand(const int & timeDifference) const;

    // Convert time to minutes past midnight
    int convertTimeToMinutes(int hour, int min) const;

    // Return the absolute time difference from current to target time in minutes
    // (how much forward the clock has to be turned)
    int computeTime(int hour1, int hour2, int min1, int min2) const;


private:
    // Disable copy ctor
    ClockApplication(ClockApplication const &) = delete;

    // Disable assignment operator
    ClockApplication operator=(const ClockApplication &) = delete;

    // TODO tutki voiko näistä poistaa jotain

    // Private members inherited from BaseApplication
    /*Ogre::Root*                 mRoot;
    Ogre::Camera*               mCamera;
    Ogre::SceneManager*         mSceneMgr;
    Ogre::RenderWindow*         mWindow;
    Ogre::String                mResourcesCfg;
    Ogre::String                mPluginsCfg;

    Ogre::OverlaySystem*        mOverlaySystem;

    // OgreBites
    OgreBites::InputContext     mInputContext;
    OgreBites::SdkTrayManager*	mTrayMgr;
    OgreBites::SdkCameraMan*    mCameraMan;     	// Basic camera controller
    OgreBites::ParamsPanel*     mDetailsPanel;   	// Sample details panel
    bool                        mCursorWasVisible;	// Was cursor visible before dialog appeared?
    bool                        mShutDown;

    //OIS Input devices
    OIS::InputManager*          mInputManager;
    OIS::Mouse*                 mMouse;
    OIS::Keyboard*              mKeyboard;

    // Added for Mac compatibility
    Ogre::String                 m_ResourcePath; */


    // Clock application related variables
    Ogre::Entity* hourHand;
    Ogre::Entity* minuteHand;
    Ogre::Entity* clockFace;
    Ogre::SceneNode* hourHandNode;
    Ogre::SceneNode* minuteHandNode;
    Ogre::SceneNode* clockFaceNode;
    int currentHours;
    int currentMinutes;
};

}
#endif // ClockApplication_H
