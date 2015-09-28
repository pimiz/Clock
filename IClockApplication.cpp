#include "IClockApplication.h"
#include "ClockApplication.h"

namespace IClockApplication {

/*
std::unique_ptr<IClockApplication*> createObject()
{
    return std::unique_ptr<ClockApplication>(new ClockApplication());
}
*/

IClockApplication * createObject()
{
    return new Clock::ClockApplication();
}

}
