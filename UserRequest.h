#ifndef IUSERREQUEST_H
#define IUSERREQUEST_H

#include <array>
#include <memory>
#include "CommonDefines.h"

namespace Clock
{
    class UserRequest;
}

typedef std::shared_ptr<Clock::UserRequest> userRequest;

namespace Clock
{

enum class UserRequestCommand {SET_TIME = 1, CHANGE_COLOR = 2};

class UserRequest
{
public:
    UserRequest(UserRequestCommand p_command) : command_(p_command) {};

    virtual ~UserRequest() {};
    UserRequestCommand getCommand()
    {
        return command_;
    }


protected:
    virtual void construct(recvBuffer const & buffer) {};
    UserRequestCommand command_;
};

userRequest createUserRequestObject(UserRequestCommand const p_command, recvBuffer const &p_buffer);

}

#endif
