#ifndef IUSERREQUEST_H
#define IUSERREQUEST_H

#include <array>
#include <memory>

namespace Clock
{
    class IUserRequest;
}

typedef std::shared_ptr<Clock::IUserRequest> userRequest;

// TODO rename this class because it is an abstract base class, not an interface

namespace Clock
{

enum class UserRequestCommand {SET_TIME = 1, CHANGE_COLOR = 2};

class IUserRequest
{
public:
    IUserRequest(UserRequestCommand p_command) : command_(p_command) {};

    virtual ~IUserRequest() {};
    UserRequestCommand getCommand()
    {
        return command_;
    }


protected:
    virtual void construct(std::array<char, 64> const &buffer) {};
    UserRequestCommand command_;
};

userRequest createUserRequestObject(UserRequestCommand const p_command, std::array<char, 64> const &p_buffer);

}

#endif
