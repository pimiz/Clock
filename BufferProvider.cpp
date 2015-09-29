#include "BufferProvider.h"

recvBuffer& BufferProvider::getRecvBuffer()
{
    static std::array<int, RECVBUFFER_SIZE> buffer;
    return buffer;
}

sendBuffer& BufferProvider::getSendBuffer()
{
    static std::array<int, SENDBUFFER_SIZE> buffer;
    return buffer;
}


void BufferProvider::clearRecvBuffer()
{
    std::array<int, RECVBUFFER_SIZE> buffer = BufferProvider::getRecvBuffer();
    buffer.fill(0);
}

int BufferProvider::getRecvBufferSize()
{
    return BufferProvider::getRecvBuffer().size();
}
