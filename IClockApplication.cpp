#include "IClockApplication.h"
#include "ClockApplication.h"

namespace ClockPublic {

std::unique_ptr<IClockApplication> createClockAppObject()
{
    return std::unique_ptr<Clock::ClockApplication>(new Clock::ClockApplication());
}

}
