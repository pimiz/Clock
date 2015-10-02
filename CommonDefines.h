#define RECVBUFFER_SIZE 64
#define SENDBUFFER_SIZE 64
#define CONSOLE_OUTPUT(X) std::cout << X << std::endl;
#define CONSOLE_OUTPUT_ERROR(X) std::cerr << X << std::endl;
typedef std::array<char, RECVBUFFER_SIZE> recvBuffer;
typedef std::array<char, SENDBUFFER_SIZE> sendBuffer;
