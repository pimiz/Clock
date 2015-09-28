#ifndef CLOCKEXCEPTION_H
#define CLOCKEXCEPTION_H

#include <stdexcept>

namespace Clock {

class ClockException : public std::exception
{
public:
    /** Constructor (C++ STL strings) */
    explicit ClockException(const std::string& message):
      msg_(message)
      {}

    /** Destructor.
     * Virtual to allow for subclassing */
    virtual ~ClockException() throw (){}

    /** Returns the error description */
    virtual char const * what() const throw() {
           return msg_.c_str();
        }

protected:
    /** Error message */
    std::string msg_;
};
}
#endif
