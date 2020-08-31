#include "PhoenixConnection.hpp"

PhoenixConnection::PhoenixConnection(const char* deviceId, const char* deviceName, const char* websocketUrl, const char* origin, const boolean* acMode, const boolean* rgbMode)
{
    this -> deviceId = deviceId;
    this -> deviceName = deviceName;
    this -> websocketUrl = websocketUrl;
    this -> acMode = acMode;
    this -> rgbMode = rgbMode;

    setDefaultJoinCallback();
    setDefaultLeaveCallback();
    setDefaultMessageCallback();
    setEventCallback();          

    client.addHeader("Origin", origin);
}

PhoenixConnection& PhoenixConnection::connect()
{   
    client.connect(websocketUrl);
    lastHeartBeat = millis();
    return *this;
}

PhoenixConnection& PhoenixConnection::join()
{
    const char* typePayload;

    if(*acMode && *rgbMode)
        typePayload = "\"types\":[\"acMode\",\"rgbMode\"]";
    else if(*acMode)
        typePayload = "\"types\":[\"acMode\"]";
    else if(*rgbMode)
        typePayload = "\"types\":[\"rgbMode\"]";
    else
        typePayload = "\"types\":[]";

    const char *join_template = "{\"topic\":\"controller:%s\",\"event\":\"phx_join\",\"payload\":{\"name\":\"%s\",%s},\"ref\":0}";
    char *result = static_cast<char*>(malloc(strlen(join_template) + strlen(deviceId) - 2 + strlen(deviceName) - 2 + strlen(typePayload) - 2 + 1));
    sprintf(result, join_template, deviceId, deviceName, typePayload);
    client.send(result);
    free(result);

    lastHeartBeat = millis();

    return *this;
}

PhoenixConnection& PhoenixConnection::setJoinCallback(const EmptyMethod& joinCallback)
{
    this -> joinCallback = joinCallback;
    return *this;
}

PhoenixConnection& PhoenixConnection::setLeaveCallback(const EmptyMethod& leaveCallback)
{
    this -> leaveCallback = leaveCallback;
    return *this;
}

PhoenixConnection& PhoenixConnection::setMessageCallback(const PartialMessageCallback& messageCallback)
{
    client.onMessage(messageCallback);
    return *this;
}

boolean PhoenixConnection::isConnected()
{
    return client.available(true);
}

void PhoenixConnection::sendHeartbeat()
{
    if(isConnected() && (millis() - lastHeartBeat >= 10000))
    {
        client.send("{\"topic\":\"phoenix\",\"event\":\"heartbeat\",\"payload\":{},\"ref\":0}");
        lastHeartBeat = millis();
    }
}

void PhoenixConnection::sendPayload(const char* payload, const long ref)
{
    const char *messageTemplate = "{\"topic\":\"controller:%s\",\"event\":\"update\",\"payload\":%s,\"ref\":%d}";
    char* toSend = static_cast<char*>(malloc(strlen(messageTemplate) + strlen(deviceId) - 2 + strlen(payload) + (ref/10 + 1) - 2 + 1));
    sprintf(toSend, messageTemplate, deviceId, payload, ref);
    client.send(toSend);
    free(toSend);
}

void PhoenixConnection::poll()
{
    client.poll();
}

void PhoenixConnection::setDefaultMessageCallback()
{
    client.onMessage([this](WebsocketsMessage message) {
        Serial.print("Got text from the server: ");
        Serial.println(message.data());
    });
}

void PhoenixConnection::setDefaultJoinCallback()
{
    joinCallback = [this](){
            Serial.print("\n\n--- Connected to Phoenix channel as '");
            Serial.print(deviceName);
            Serial.print("' (");
            Serial.print(deviceId);
            Serial.println(") ---\n");
            digitalWrite(STATUS_LED, LOW);
    };
}

void PhoenixConnection::setDefaultLeaveCallback()
{
    leaveCallback = [](){
        Serial.println("\n\n--- Disconnected from Phoenix channel ---\n");
        digitalWrite(STATUS_LED, HIGH);
    };
}

void PhoenixConnection::setEventCallback()
{
    client.onEvent([this](WebsocketsEvent event, String message) {
        if(event == WebsocketsEvent::ConnectionOpened)
            joinCallback();
        else if(event == WebsocketsEvent::ConnectionClosed)
            leaveCallback();
    });
}