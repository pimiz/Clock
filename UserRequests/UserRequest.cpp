#include <memory>
#include "UserRequest.h"
#include "UserRequestSetColours.h"
#include "UserRequestSetTime.h"
#include "ClockException.h"


namespace Clock
{
UserRequestPtr createUserRequestObject(UserRequestCommand const p_command, RecvBuffer const &p_buffer)
{
    switch (p_command)
    {
        case UserRequestCommand::SET_TIME:
            return std::make_shared<UserRequestSetTime>(p_buffer);
        case UserRequestCommand::SET_COLOURS:
            return std::make_shared<UserRequestSetColours>(p_buffer);
        default:
            throw Clock::ClockException(std::string("Invalid command requested: ")
                                        + std::to_string(static_cast<int>(p_command)));
            break;
    }
    return nullptr;
}
}
