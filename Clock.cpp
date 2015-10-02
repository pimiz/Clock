#include <iostream>
#include <memory>
#include "IClockApplication.h"
#include "ClockException.h"
#include "CommonDefines.h"

using namespace ClockPublic;

extern "C" {

int main(int argc, char *argv[])
    {
        /* Create application object */
        std::unique_ptr<IClockApplication> app = createClockAppObject();

        try
        {
            app->go();
        }
        catch(Ogre::Exception& e)
        {
            CONSOLE_OUTPUT_ERROR(std::string("An OGRE exception has occured: ")
                                 + e.getFullDescription())
        }
        catch (Clock::ClockException &e)
        {
            CONSOLE_OUTPUT_ERROR(std::string("A clock exception has occured: ")
                                 +e.what())
        }

        return 0;
    }
}
