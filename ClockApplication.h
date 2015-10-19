/* ClockApplication.h - header for ClockApplication class
* -------------------------------------------------------
* ClockApplication is derived from class BaseApplication,
* which is a part of OGRE3D tutorial framework. It manages
* objects related to renderable 3D scene, utilizes OGRE's
* services and processes user requests. */

#ifndef CLOCKAPPLICATION_H
#define CLOCKAPPLICATION_H

#include <memory>
#include "BufferProvider.h"
#include "IClockApplication.h"
#include "IClockAdjuster.h"
#include "UserRequests/UserRequest.h"


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
    void setClockFaceColour(std::string const & p_clockFaceRGB) override;
    void setHourHandColour(std::string const & p_hourHandRGB) override;
    void setMinuteHandColour(std::string const & p_minuteHandRGB) override;

protected:
    int convertTimeToMinutes(int const p_hour, int const p_min) const;
    int computeTimeDifference(int const p_hour1, int const p_hour2, int const p_min1, int const p_min2) const;
    int getCurrentTime();
    UserRequestPtr parseUserRequest(RecvBuffer const & p_buffer);
    bool runEventLoop();
    void setHourHand(int const & p_timeDifference) const;
    void setMinuteHand(int const & p_timeDifference) const;
    Ogre::ColourValue parseToColourValue(std::string const & p_rgbValue) const;
    void setAmbientColourValue(Ogre::MaterialPtr const & p_material, std::string const & p_RGB);


private:
    /* Disable copy ctor and assignment operator */
    ClockApplication(ClockApplication const &) = delete;
    ClockApplication operator=(const ClockApplication &) = delete;

    /* Clock application related variables */
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
