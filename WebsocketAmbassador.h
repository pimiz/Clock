#ifndef WEBSOCKETAMBASSADOR_H
#define WEBSOCKETAMBASSADOR_H

#define WSAMB_RECVBUFFER_SIZE 64
#define WSAMB_SENDBUFFER_SIZE 64

class WebsocketAmbassador
{
    public:
        static WebsocketAmbassador& getInstance();

        static char* getRecvBuffer();
        static char* getSendBuffer();
        static void clearBuffer();
        static int getRecvBufferSize();

    private:
        WebsocketAmbassador() {};

        WebsocketAmbassador(WebsocketAmbassador const&);              // Don't Implement
        void operator=(WebsocketAmbassador const&); // Don't implement
};

#endif
