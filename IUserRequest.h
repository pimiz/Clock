#ifndef IUSERREQUEST_H
#define IUSERREQUEST_H

namespace Clock
{

enum class UserRequestCommand {SET_TIME, CHANGE_COLOR};

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
    UserRequestCommand command_;
};

IUserRequest * createUserRequestObject(UserRequestCommand p_command);

}

#endif
