#ifndef USERREQUESTSETCOLOURS_H
#define USERREQUESTSETCOLOURS_H

#include "UserRequest.h"
namespace Clock
{
/* user request for changing colours of clock face and hands */
class UserRequestSetColours : public UserRequest
{
public:
    UserRequestSetColours(RecvBuffer const & p_buffer);
    ~UserRequestSetColours();
    void process(ClockAdjusterPtr const & p_clockApp) const override;

protected:
    void construct(RecvBuffer const & p_buffer) override;

private:
    /* disable default ctor, copy ctor and assignment operator */
    UserRequestSetColours() = delete;
    UserRequestSetColours(const UserRequestSetColours &) = delete;
    UserRequestSetColours operator=(const UserRequestSetColours &) = delete;

    /* storable data parsed from user request */
    std::string m_clockFaceColour;
    std::string m_hourHandColour;
    std::string m_minuteHandColour;
};

}
#endif

