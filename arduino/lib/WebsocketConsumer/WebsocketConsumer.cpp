#include "WebsocketConsumer.hpp"
#include <ArduinoWebsockets.h>
#include <ArduinoJson.hpp>
#include <ArduinoJson.h>
#include <IRmanager.hpp>

using namespace websockets;

IRmanager manager(D6);

#define TESTING_AC true 

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

        #if TESTING_AC
            ACdata data;
            // Booleans
            data.power           = true;
            data.eco             = false;
            data.health          = false;
            data.light           = true;
            data.turbo           = false;
            data.horizontalSwing = false;
            data.verticalSwing   = false;
            // Integers
            data.mode            = 8;
            data.fan             = 0;
            // Floats
            data.temp            = 22.5;
            manager.sendACdata(data);
            delay(1000);
            data.light = false;
            manager.sendACdata(data);
            delay(1000);
            data.light = true;
            manager.sendACdata(data);
        #else
            manager.sendRaw(code);
        #endif
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