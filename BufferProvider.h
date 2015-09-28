#ifndef BUFFERPROVIDER_H
#define BUFFERPROVIDER_H

#define RECVBUFFER_SIZE 64
#define SENDBUFFER_SIZE 64

class BufferProvider
{
    public:
        static char* getRecvBuffer();
        static char* getSendBuffer();
        static void clearBuffer();
        static int getRecvBufferSize();

    private:
        BufferProvider() {};

        // Disable copy ctor
        BufferProvider(BufferProvider const&);
        // Disable assignment operator
        void operator=(BufferProvider const&);
};

#endif
