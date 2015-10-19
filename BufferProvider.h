/* BufferProvider.h - header for BufferProvider
 * --------------------------------------------
/* class BufferProvider: A singleton class which provides two
 * buffers to transfer data between components bidirectionally. */


#ifndef BUFFERPROVIDER_H
#define BUFFERPROVIDER_H
#include <memory>
#include "CommonDefines.h"

using Clock::RecvBuffer;
using Clock::SendBuffer;

class BufferProvider
{
    public:
        static RecvBuffer& getRecvBuffer();
        static SendBuffer& getSendBuffer();
        static void clearRecvBuffer();
        static void clearSendBuffer();
        static int getReceivedBytes();
        static int getSentBytes();
        /* Use a mutex to make the buffers thread-safe */
        static std::mutex& getMutex();

    private:
        /* Disable default ctor, copy ctor and assignment operator */
        BufferProvider() {};
        BufferProvider(BufferProvider const &);
        void operator=(BufferProvider const &);
};

#endif
