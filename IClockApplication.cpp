#include "IClockApplication.h"
#include "ClockApplication.h"

using Clock::ClockApplicationPtr;

namespace ClockPublic {

ClockApplicationPtr createClockAppObject()
{
    return std::shared_ptr<Clock::ClockApplication>(new Clock::ClockApplication());
}

}
