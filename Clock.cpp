#include "ClockApplication.h"
#include "WebsocketInterface.h"
#include <iostream>

extern "C" {

int main(int argc, char *argv[])
    {
        WebsocketInterface::init();

        // Create application object
        ClockApplication app;

        try
        {
           app.go();
        }
        catch( Ogre::Exception& e )
        {
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
        }


        WebsocketInterface::finish();
        return 0;
    }
}
