#ifndef ICLOCKAPPLICATION_H
#define ICLOCKAPPLICATION_H

#include <memory> // std::unique_ptr
#include "BaseApplication.h"

// TODO nää pois tästä kokonaan tai sit jonnekin muualle
#define CONSOLE_OUTPUT(X) std::cout << X << std::endl;
#define CONSOLE_OUTPUT_ERROR(X) std::cerr << X << std::endl;

namespace IClockApplication {

class IClockApplication : public BaseApplication
{
public:
    virtual ~IClockApplication() {};

    // Functions inherited from BaseApplication
    virtual void go() = 0;
    virtual void createScene() = 0;

    // TODO get rid of this?
    virtual int getCurrentTime() =0;
};

// to only expose the interface instead of class name to caller

//std::unique_ptr<IClockApplication> createObject();
IClockApplication * createObject();

} // namespace
#endif // ICLOCKAPPLICATION_H
