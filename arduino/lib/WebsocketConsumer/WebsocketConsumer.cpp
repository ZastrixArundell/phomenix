#include "WebsocketConsumer.hpp"
#include <ArduinoWebsockets.h>
#include <ArduinoJson.hpp>
#include <ArduinoJson.h>
#include <IRsend.h>

using namespace websockets;

IRsend irsend(D6);

uint32_t transalteCode(String& code)
{
    return strtoul(code.c_str(), NULL, 10);
}

void websocket_consumer::consumeMessage(const WebsocketsMessage& message)
{
    Serial.print("Using consumer on: ");
    Serial.println(message.data());

    DynamicJsonDocument doc(400);
    deserializeJson(doc, message.data());

    String event = doc["event"];
    
    if(event == "ir_write")
    {
        String code = doc["payload"]["code"];
        irsend.sendNEC(transalteCode(code));
    }
}