#include "IUserRequest.h"
#include "UserRequests.h"

namespace Clock
{
IUserRequest * createUserRequestObject(UserRequestCommand p_command)
{
    switch (p_command)
    {
        case UserRequestCommand::SET_TIME:
            return new UserRequestSetTime();
            break;
        default:
            break;
    }
    return nullptr;
}
}
