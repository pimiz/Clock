#ifndef USERREQUESTS_H
#define USERREQUESTS_H

#include "IUserRequest.h"

namespace Clock
{

class UserRequestSetTime : public IUserRequest
{
public:
    UserRequestSetTime();
    UserRequestSetTime(std::array<char, 64> const &buffer);

    ~UserRequestSetTime();

    void setHours(const int p_hours);
    void setMinutes(const int p_minutes);

    int getHours() const;

    int getMinutes() const;

    /* Get time in minutes past 00:00 (or possibly 12:00, if time given originally in 24h format) */
    int getTimeInMinutesPastZero() const;

protected:
    void construct(std::array<char, 64> const &buffer) override;

private:
    UserRequestSetTime(const UserRequestSetTime&) = delete;
    UserRequestSetTime operator=(const UserRequestSetTime &) = delete;



    int getTimeInMinutesPastZero(const int p_hours, const int p_minutes) const;

    int hours_;
    int minutes_;
};

}

#endif
