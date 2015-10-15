#include <mutex>
#include "BufferProvider.h"
#include <iostream>

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
    RecvBuffer & buf = BufferProvider::getRecvBuffer();
    int bytes = atoi(std::string(buf.begin(), USERREQUEST_SIZE_LENGTH).c_str());
    return bytes;
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
