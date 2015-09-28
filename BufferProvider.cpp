#include <cstring>
#include "BufferProvider.h"

char* BufferProvider::getRecvBuffer()
{
    static char buffer[RECVBUFFER_SIZE];
    return buffer;
}

char* BufferProvider::getSendBuffer()
{
    static char buffer[SENDBUFFER_SIZE];
    return buffer;
}

void BufferProvider::clearBuffer()
{
    char * buffer = getRecvBuffer();
    memset(&buffer[0], 0, RECVBUFFER_SIZE);
}

int BufferProvider::getRecvBufferSize()
{
    return strlen(getRecvBuffer());
}
