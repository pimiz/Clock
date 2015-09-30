#ifndef BUFFERPROVIDER_H
#define BUFFERPROVIDER_H
#include <array>
#include <mutex>

#define RECVBUFFER_SIZE 64
#define SENDBUFFER_SIZE 64

typedef std::array<char, RECVBUFFER_SIZE> recvBuffer;
typedef std::array<char, SENDBUFFER_SIZE> sendBuffer;

class BufferProvider
{
    public:
        static recvBuffer& getRecvBuffer();
        static sendBuffer& getSendBuffer();
        static void clearRecvBuffer();
        static void clearSendBuffer();
        static int getReceivedBytes();
        static int getSentBytes();

        /* Use a mutex to make the buffers thread-safe */
        static std::mutex& getMutex();

    private:
        BufferProvider() {};

        // Disable copy ctor
        BufferProvider(BufferProvider const&);
        // Disable assignment operator
        void operator=(BufferProvider const&);

};

#endif
