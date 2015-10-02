#include <memory>
#include "UserRequest.h"
#include "UserRequests.h"
#include "ClockException.h"


namespace Clock
{
userRequest createUserRequestObject(UserRequestCommand const p_command, recvBuffer const &p_buffer)
{
    switch (p_command)
    {
        case UserRequestCommand::SET_TIME:
            return std::make_shared<UserRequestSetTime>(p_buffer);
            break;
        default:
            throw Clock::ClockException(std::string("Invalid command requested: ")
                                        + std::to_string(static_cast<int>(p_command)));
            break;
    }
    return nullptr;
}
}
