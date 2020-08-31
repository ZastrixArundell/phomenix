#include "WebsocketConsumer.hpp"
#include <ArduinoWebsockets.h>
#include <ArduinoJson.hpp>
#include <ArduinoJson.h>
#include <IRmanager.hpp>

using namespace websockets;

IRmanager manager(D6);

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
        manager.sendRaw(code);
    }
    else if(event == "ac_write")
    {
        ACdata data;
        // Booleans
        data.power           = doc["payload"]["power"];
        data.eco             = doc["payload"]["eco"];
        data.health          = doc["payload"]["health"];
        data.light           = doc["payload"]["light"];
        data.turbo           = doc["payload"]["turbo"];
        data.horizontalSwing = doc["payload"]["horizontalSwing"];
        data.verticalSwing   = doc["payload"]["verticalSwing"];
        // Integers
        data.mode            = doc["payload"]["mode"];
        data.fan             = doc["payload"]["fan"];
        // Floats
        data.temp            = doc["payload"]["temp"];
        manager.sendACdata(data);
    }
}