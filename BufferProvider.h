#ifndef BUFFERPROVIDER_H
#define BUFFERPROVIDER_H
#include <array>

#define RECVBUFFER_SIZE 64
#define SENDBUFFER_SIZE 64

typedef std::array<int, RECVBUFFER_SIZE> recvBuffer;
typedef std::array<int, SENDBUFFER_SIZE> sendBuffer;

class BufferProvider
{
    public:
        static recvBuffer& getRecvBuffer();
        static sendBuffer& getSendBuffer();
        static void clearRecvBuffer();

        static int getRecvBufferSize();

    private:
        BufferProvider() {};

        // Disable copy ctor
        BufferProvider(BufferProvider const&);
        // Disable assignment operator
        void operator=(BufferProvider const&);
};

#endif
