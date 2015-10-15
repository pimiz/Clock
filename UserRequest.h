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

    virtual void process(ClockAdjusterPtr const & clockApp) const = 0;


protected:
    virtual void construct(RecvBuffer const & buffer) {};
    UserRequestCommand command_;
};

UserRequestPtr createUserRequestObject(UserRequestCommand const p_command, RecvBuffer const &p_buffer);

}

#endif
