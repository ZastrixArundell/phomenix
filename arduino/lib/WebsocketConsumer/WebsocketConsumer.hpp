#ifndef WEBSOCKET_CONSUMER_H
#define WEBSOCKET_CONSUMER_H

#include <ArduinoWebsockets.h>

namespace websocket_consumer
{
    void consumeMessage(const websockets::WebsocketsMessage& message);
};

#endif