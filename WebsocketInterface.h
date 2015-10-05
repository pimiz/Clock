#ifndef WEBSOCKETINTERFACE_H
#define WEBSOCKETINTERFACE_H

#include <libwebsockets.h>
#include "BufferProvider.h"
#include "CommonDefines.h"

// Call the buffer provider WebsocketAmbassador to clarify its purpose on this app
using WebsocketAmbassador = BufferProvider;

namespace WebsocketInterface {

    int init();
    void finish();

    void runService();

    static int my_protocol_callback(struct libwebsocket_context *context,
             struct libwebsocket *wsi,
             enum libwebsocket_callback_reasons reason,
             void *user, void *in, size_t len);

    static int callback_http(struct libwebsocket_context *context,
             struct libwebsocket *wsi,
             enum libwebsocket_callback_reasons reason, void *user,
             void *in, size_t len);
    static void sighandler(int sig);

    //struct libwebsocket_context *context;


    //**************************************************************************//
    /* list of supported protocols and callbacks */
    //**************************************************************************//
    static struct libwebsocket_protocols protocols[] = {
    /* first protocol must always be HTTP handler */
    {
         "http-only", // name
         callback_http, // callback
         0 // per_session_data_size
    },
    {
        "my-protocol",
        my_protocol_callback,
        30,
        RECVBUFFER_SIZE,
    },
    { NULL, NULL, 0, 0 }

    }; /* terminator */
}

#endif
