#ifndef ICLOCKAPPLICATION_H
#define ICLOCKAPPLICATION_H

#include <memory> // std::unique_ptr
#include "BaseApplication.h"


namespace ClockPublic {

class IClockApplication : public BaseApplication
{
public:
    virtual ~IClockApplication() {};

    // Functions inherited from BaseApplication
    virtual void go() = 0;
    virtual void createScene() = 0;
};

/* Use interface class pattern to only expose the interface
 * instead of actual class name to caller */

std::unique_ptr<IClockApplication> createClockAppObject();

} // namespace
#endif // ICLOCKAPPLICATION_H
