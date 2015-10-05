#include <mutex>
#include "BufferProvider.h"

RecvBuffer& BufferProvider::getRecvBuffer()
{
    static RecvBuffer buffer;
    return buffer;
}

SendBuffer& BufferProvider::getSendBuffer()
{
    static SendBuffer buffer;
    return buffer;
}

void BufferProvider::clearRecvBuffer()
{
    RecvBuffer &buffer = BufferProvider::getRecvBuffer();
    buffer.fill('0');
}

void BufferProvider::clearSendBuffer()
{
    SendBuffer &buffer = BufferProvider::getSendBuffer();
    buffer.fill('0');
}

int BufferProvider::getReceivedBytes()
{
    char size = BufferProvider::getRecvBuffer().front();
    return atoi(&size);
}

int BufferProvider::getSentBytes()
{
    char size = BufferProvider::getSendBuffer().front();
    return atoi(&size);
}

std::mutex& BufferProvider::getMutex()
{
    static std::mutex mutex;
    return mutex;
}
