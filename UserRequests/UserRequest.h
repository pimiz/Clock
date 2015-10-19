/* UserRequest.h - header for UserRequest objects
 * ----------------------------------------------
 * Base class for all user requests from websocket interface. */

#ifndef IUSERREQUEST_H
#define IUSERREQUEST_H

#include <array>
#include <memory>
#include "CommonDefines.h"

namespace Clock
{
    enum class UserRequestCommand {SET_TIME = 1, SET_COLOURS = 2};

class UserRequest
{
public:
    UserRequest(UserRequestCommand p_command) : command_(p_command) {}
    virtual ~UserRequest() {}
    UserRequestCommand getCommand()
    {
        return command_;
    }

    /* the "do your magic"-function. in order to support user requests,
     * the clock application class needs to implement interface IClockAdjuster. */
    virtual void process(ClockAdjusterPtr const & clockApp) const = 0;


protected:
    /* construct the user request object according to user inputted data
     * that is read from a buffer */
    virtual void construct(RecvBuffer const & buffer) {};
    UserRequestCommand command_;
};

/* Use interface class pattern to only expose the interface
 * instead of actual class name to caller */
UserRequestPtr createUserRequestObject(UserRequestCommand const p_command, RecvBuffer const &p_buffer);

}

#endif
