#include <array>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <syslog.h>

#include <signal.h>
#include <mutex>
#include <libwebsockets.h>
#include <string>

#include <iomanip>
#include <sstream>

#include "WebsocketInterface.h"
#include "BufferProvider.h"
#include "ClockException.h"

#include <iostream> //debug

using Clock::MutexGuard;

namespace WebsocketInterface {

int force_exit = 0;
libwebsocket_context *context;

int init()
{
    int n = 0;
    //struct libwebsocket_context *context;
    int opts = 0;
    const char *iface = NULL;
    int syslog_options = LOG_PID | LOG_PERROR;
    unsigned int oldus = 0;
    struct lws_context_creation_info info;

    int debug_level = 7;

    memset(&info, 0, sizeof info);
    info.port = 9999;


    signal(SIGINT, sighandler);

    /* we will only try to log things according to our debug_level */
    setlogmask(LOG_UPTO (LOG_DEBUG));
    openlog("lwsts", syslog_options, LOG_DAEMON);

    /* tell the library what debug level to emit and to send it to syslog */
    lws_set_log_level(debug_level, lwsl_emit_syslog);

    info.iface = iface;
    info.protocols = protocols;
    info.extensions = libwebsocket_get_internal_extensions();
        info.ssl_cert_filepath = NULL;
        info.ssl_private_key_filepath = NULL;

    info.gid = -1;
    info.uid = -1;
    info.options = opts;

    context = libwebsocket_create_context(&info);
    if (context == NULL) {
        lwsl_err("libwebsocket init failed\n");
        return -1;
    }

    closelog();

    return 0;
}//main

void finish()
{
    libwebsocket_context_destroy(context);
}


void runService()
{
    libwebsocket_service(context, 10);
}

int my_protocol_callback(struct libwebsocket_context *context,
             struct libwebsocket *wsi,
             enum libwebsocket_callback_reasons reason,
                 void *user, void *in, size_t len)
{
    unsigned char buf[LWS_SEND_BUFFER_PRE_PADDING + 512 +
                          LWS_SEND_BUFFER_POST_PADDING];

    switch (reason) {

    case LWS_CALLBACK_ESTABLISHED:
            CONSOLE_OUTPUT("New Connection");
        break;

    case LWS_CALLBACK_SERVER_WRITEABLE:
        break;

    case LWS_CALLBACK_RECEIVE:
    {
        /* message from client received.
           check if length of received data is in allowed limits.
           two bytes are reserved for length information */
        if (len > RECVBUFFER_SIZE - 2)
        {
            throw Clock::ClockException(std::string("Too large data callback from Websocket interface (") + std::to_string(len) + ") bytes");
        }

        MutexGuard lock(WebsocketAmbassador::getMutex());
        RecvBuffer& recvBuf = WebsocketAmbassador::getRecvBuffer();

        /* check if an instant response is required, i.e. do we find
           a special character as the first byte */
        char firstByte;
        memcpy(&firstByte, static_cast<char*>(in), 1);

        if (firstByte == TIMEREQUEST_CHAR)
        {
            /* respond with current time shown on the clock */
            SendBuffer &sendBuf = WebsocketAmbassador::getSendBuffer();
            int sendDataSize = 0;
            memcpy(&sendDataSize, &sendBuf[0], sizeof(sendBuf[0]));
            for (int i=0; i <= sendDataSize; i++) {
                buf[LWS_SEND_BUFFER_PRE_PADDING + i ] = sendBuf[i+1];
            }
            libwebsocket_write(wsi, &buf[LWS_SEND_BUFFER_PRE_PADDING], sendDataSize, LWS_WRITE_TEXT);
        }
        else
        {
            /* store length of received data to first two elements of buffer */
            std::stringstream ss;
            ss << std::setfill('0') << std::setw(2) << len << std::endl;
            std::string lenStr = ss.str();
            lenStr.copy(&recvBuf[USERREQUEST_SIZE_POSITION], USERREQUEST_SIZE_LENGTH);

            /* copy received data to buffer after size information for further processing */
            memcpy(&recvBuf[USERREQUEST_SIZE_POSITION + USERREQUEST_SIZE_LENGTH], in, len);
        }
    }
    case LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION:
        break;

    default:
        break;
    }

    return 0;
}

int callback_http(struct libwebsocket_context *context,
                         struct libwebsocket *wsi,
                         enum libwebsocket_callback_reasons reason, void *user,
                         void *in, size_t len)
{
    return 0;
}

//**************************************************************************//
void sighandler(int sig)
{
    force_exit = 1;
}
//**************************************************************************//

}
