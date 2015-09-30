#include "BufferProvider.h"

recvBuffer& BufferProvider::getRecvBuffer()
{
    static recvBuffer buffer;
    return buffer;
}

sendBuffer& BufferProvider::getSendBuffer()
{
    static sendBuffer buffer;
    return buffer;
}

void BufferProvider::clearRecvBuffer()
{
    recvBuffer &buffer = BufferProvider::getRecvBuffer();
    buffer.fill('0');
}

void BufferProvider::clearSendBuffer()
{
    sendBuffer &buffer = BufferProvider::getSendBuffer();
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
