#include <QCoreApplication>
#include <ClockApplication.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ClockApplication app;
    try {
        app.go();
    } catch(Ogre::Exception& e)
    {
        std::cerr << "An exception has occurred: " << e.getFullDescription().c_str() << std::endl;
        return EXIT_FAILURE;
    }

    return a.exec();
}
