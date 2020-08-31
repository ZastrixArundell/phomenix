#ifndef PHOENIXCONNECTIONS_H
#define PHOENIXCONNECTIONS_H

#include <ESP8266WiFi.h>
#include <ArduinoWebsockets.h>
// https://github.com/gilmaimon/ArduinoWebsockets

#define STATUS_LED 16

using namespace websockets;
typedef std::function<void ()> EmptyMethod;

/*
    C++ class representing the connection to the Phoenix channels. 
    It has default and custom behaviours. 
*/
class PhoenixConnection
{
        WebsocketsClient client;
        const char *deviceId, *deviceName, *websocketUrl;
        unsigned long lastHeartBeat;
        EmptyMethod joinCallback, leaveCallback;
        const boolean *acMode, *rgbMode;
    public:
        PhoenixConnection(const char* deviceId, const char* deviceName, const char* websocketUrl, const char* origin, const boolean* acMode, const boolean* rgbMode);
        PhoenixConnection& connect();
        PhoenixConnection& join();
        PhoenixConnection& setJoinCallback(const EmptyMethod& joinCallback);
        PhoenixConnection& setLeaveCallback(const EmptyMethod& leaveCallback);
        PhoenixConnection& setMessageCallback(const PartialMessageCallback& messageCallback);
        boolean isConnected();
        void sendHeartbeat();
        void sendPayload(const char* payload, const long ref = 0);
        void poll();
    private:
        void setDefaultMessageCallback();
        void setDefaultJoinCallback();
        void setDefaultLeaveCallback();
        void setEventCallback();
};

#endif