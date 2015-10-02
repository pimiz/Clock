#ifndef BUFFERPROVIDER_H
#define BUFFERPROVIDER_H
#include <array>
#include <memory>
#include <mutex>
#include "CommonDefines.h"
#include "ITimeRequester.h"

class BufferProvider
{
    public:
        static recvBuffer& getRecvBuffer();
        static sendBuffer& getSendBuffer();
        static void clearRecvBuffer();
        static void clearSendBuffer();
        static int getReceivedBytes();
        static int getSentBytes();
        static void setTimeRequester(std::unique_ptr<TimeRequester::ITimeRequester> requester);

        /* Use a mutex to make the buffers thread-safe */
        static std::mutex& getMutex();

    private:
        /* Disable default ctor */
        BufferProvider() {};
        /* Disable copy ctor */
        BufferProvider(BufferProvider const &);
        /* Disable assignment operator */
        void operator=(BufferProvider const &);
};

#endif
