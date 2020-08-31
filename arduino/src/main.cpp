#include <ESP8266WiFi.h>
#include <Config.h>
#include <PhoenixConnection.hpp>
#include <WebsocketConsumer.hpp>

// Values specific to the WiFi connection
const char* ssid     = SSID;
const char* password = PASSWORD;

// Values specific to the WebSocket connection
const char* deviceId     = DEVICE_ID;
const char* deviceName   = DEVICE_NAME;
const char* websocketUrl = WEBSOCKET_URL;
const char* origin       = ORIGIN;

PhoenixConnection connection(deviceId, deviceName, websocketUrl, origin);

void setup()
{
    Serial.begin(115200);
    delay(100);

    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);
    WiFi.softAPdisconnect(true);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.print("WiFi connected at: ");
    Serial.print(WiFi.localIP());

    pinMode(16, OUTPUT);
    digitalWrite(16, HIGH);

    pinMode(D6, OUTPUT);

    connection
        .setMessageCallback(websocket_consumer::consumeMessage)
        .connect()
        .join();
}

void (* restart) (void) = 0;

void loop()
{
    connection.poll();
    connection.sendHeartbeat();

    if(!connection.isConnected())
        restart();
}
