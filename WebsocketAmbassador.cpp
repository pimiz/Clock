#include <cstring>
#include "WebsocketAmbassador.h"



WebsocketAmbassador& WebsocketAmbassador::getInstance()
{
    static WebsocketAmbassador instance;
    return instance;
}

char* WebsocketAmbassador::getRecvBuffer()
{
    static char buffer[WSAMB_RECVBUFFER_SIZE];
    return buffer;
}

char* WebsocketAmbassador::getSendBuffer()
{
    static char buffer[WSAMB_SENDBUFFER_SIZE];
    return buffer;
}

void WebsocketAmbassador::clearBuffer()
{
    char * buffer = getRecvBuffer();
    memset(&buffer[0], 0, WSAMB_RECVBUFFER_SIZE);
}

int WebsocketAmbassador::getRecvBufferSize()
{
    return strlen(getRecvBuffer());
}
