#include <iostream>
#include "IClockApplication.h"
#include "WebsocketInterface.h"
#include "ClockException.h"

extern "C" {

int main(int argc, char *argv[])
    {
        WebsocketInterface::init();

        // Create application object
        IClockApplication::IClockApplication * app = IClockApplication::createObject();

        try
        {
            app->go();
        }
        catch(Ogre::Exception& e)
        {
            std::cerr << "An OGRE exception has occured: " <<
                e.getFullDescription() << std::endl;
        }
        catch (Clock::ClockException &e)
        {
            std::cerr << "A clock exception has occured: " <<
                e.what() << std::endl;
        }


        WebsocketInterface::finish();
        return 0;
    }
}
