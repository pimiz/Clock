#define RECVBUFFER_SIZE 64
#define SENDBUFFER_SIZE 64
#define CONSOLE_OUTPUT(X) std::cout << X << std::endl;
#define CONSOLE_OUTPUT_ERROR(X) std::cerr << X << std::endl;

/* forward declare necessary std components to avoid unnecessary #including */
namespace std {
template<typename T, std::size_t N>
    struct array;
template<typename T>
    class lock_guard;
template<typename T>
    class shared_ptr;
    class mutex;
}

namespace ClockPublic {
    class IClockAdjuster;
    class IClockApplication;
}

namespace Clock {
    class UserRequest;

    using RecvBuffer = std::array<char, RECVBUFFER_SIZE>;
    using SendBuffer = std::array<char, SENDBUFFER_SIZE>;
    using MutexGuard = std::lock_guard<std::mutex>;
    using ClockAdjusterPtr = std::shared_ptr<ClockPublic::IClockAdjuster>;
    using ClockApplicationPtr = std::shared_ptr<ClockPublic::IClockApplication>;
    using UserRequestPtr = std::shared_ptr<Clock::UserRequest>;

}
