#ifndef CLOCKAPPLICATION_H
#define CLOCKAPPLICATION_H

#include <memory>
#include "BufferProvider.h"
#include "IClockApplication.h"
#include "IClockAdjuster.h"
#include "UserRequest.h"


namespace Clock {

class ClockApplication :
        public std::enable_shared_from_this<ClockApplication>,
        public ClockPublic::IClockApplication,
        public ClockPublic::IClockAdjuster
{
public:
    ClockApplication();
    ~ClockApplication();

    /* Functions inherited from IClockApplication */
    void go() override;
    void createScene() override;

    /* Functions inherited from IClockAdjuster */
    void adjustClock(int const p_hours, int const p_minutes) override;    
    void setClockFaceColour(std::string const & p_clockFaceRGBA) override;
    void setHourHandColour(std::string const & p_hourHandRGBA) override;
    void setMinuteHandColour(std::string const & p_minuteHandRGBA) override;

protected:
    UserRequestPtr parseUserRequest(RecvBuffer const & p_buffer);
    bool runEventLoop();

    void setHourHand(int const & p_timeDifference) const;
    void setMinuteHand(int const & p_timeDifference) const;

    Ogre::ColourValue parseToColourValue(std::string const & p_rgbaValue) const;
    void setAmbientColourValue(Ogre::MaterialPtr const & p_material, std::string const & p_RGBA);

    int convertTimeToMinutes(int const p_hour, int const p_min) const;
    // Return the absolute time difference from current to target time in minutes
    // (how much forward the clock has to be turned)
    int computeTimeDifference(int const p_hour1, int const p_hour2, int const p_min1, int const p_min2) const;

    int getCurrentTime();

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
    int m_currentHours;
    int m_currentMinutes;
};

}
#endif // ClockApplication_H
