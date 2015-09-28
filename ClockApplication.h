#ifndef ClockApplication_H
#define ClockApplication_H

#include "BaseApplication.h"

#define CONSOLE_OUTPUT(X) std::cout << X << std::endl;
#define CONSOLE_OUTPUT_ERROR(X) std::cerr << X << std::endl;


class ClockApplication : public BaseApplication
{
public:
    //ClockApplication(WebsocketInterface * p_wsInterface);
    ClockApplication();

    virtual ~ClockApplication(void);
    void go();

    static int getCurrentTime();

 protected:
    virtual void createScene(void);
    virtual void processUserRequest(char * buffer);

private:

    /* Pointer-to-implementation design pattern used here because either:
        -we do not want to reveal our implementation details publicly or
        -we do not want to recompile everything which includes ClockApplication.h after it has been modified */
    class Private;
    static Private *d;
};

#endif // ClockApplication_H
