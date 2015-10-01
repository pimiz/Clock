#include <memory>
#include "IUserRequest.h"
#include "UserRequests.h"
#include "ClockException.h"


namespace Clock
{
userRequest createUserRequestObject(UserRequestCommand const p_command, std::array<char, 64> const &p_buffer)
{
    switch (p_command)
    {
        case UserRequestCommand::SET_TIME:
            return std::make_shared<UserRequestSetTime>(p_buffer);
            break;
        default:
            throw Clock::ClockException("Invalid command requested");
            break;
    }
    return nullptr;
}
}
