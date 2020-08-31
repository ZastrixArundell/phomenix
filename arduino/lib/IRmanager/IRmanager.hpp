#ifndef IRMANAGER_H
#define IRMANAGER_H

#include <ESP8266WiFi.h>

struct ACdata
{
    boolean power, eco, health, light, turbo, horizontalSwing, verticalSwing;
    int mode, fan;
    float temp;
};

class IRmanager
{
    public:
        IRmanager(const int& ledPin);
        void sendRaw(String& raw);
        void sendACdata(ACdata& acData);
};

#endif