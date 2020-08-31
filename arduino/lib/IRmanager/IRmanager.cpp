#include "IRmanager.hpp"
#include <ESP8266WiFi.h>
#include <IRac.h>
#include <IRsend.h>

uint16_t controlData[227] = {3152, 1522,  564, 1020,  564, 1020,  564, 254,  564, 252,  564, 254,  564, 1020,  564, 252,  566, 254,  564, 1022,  564, 1022,  562, 254,  564, 1020,  564, 254,  562, 254,  564, 1022,  562, 1020,  564, 252,  564, 1018,  566, 1022,  562, 254,  564, 252,  564, 1022,  564, 254,  564, 252,  566, 254,  564, 1020,  564, 252,  564, 254,  564, 254,  564, 252,  564, 254,  566, 252,  564, 254,  564, 254,  564, 252,  564, 254,  564, 254,  564, 254,  564, 252,  564, 254,  564, 252,  566, 254,  564, 252,  566, 252,  566, 254,  564, 252,  566, 1020,  566, 250,  566, 254,  564, 252,  566, 254,  564, 254,  564, 256,  562, 254,  564, 252,  564, 254,  564, 254,  564, 252,  564, 254,  564, 252,  566, 252,  564, 254,  564, 254,  564, 254,  564, 254,  566, 252,  564, 254,  564, 252,  566, 252,  564, 252,  566, 252,  566, 252,  566, 254,  564, 254,  564, 256,  562, 254,  564, 254,  564, 254,  564, 254,  566, 252,  564, 254,  564, 252,  564, 252,  566, 254,  564, 252,  564, 254,  564, 252,  566, 252,  564, 254,  564, 254,  564, 252,  566, 252,  564, 254,  566, 252,  564, 254,  564, 252,  564, 254,  564, 254,  564, 254,  564, 252,  564, 254,  564, 254,  564, 254,  564, 254,  564, 1020,  566, 254,  564, 1020,  564, 254,  564, 254,  566, 1020,  564, 1020,  564, 254,  564};

IRTcl112Ac *ac;
IRsend     *ir;

IRmanager::IRmanager(const int& ledPin)
{
    pinMode(ledPin, OUTPUT);
    ir = new IRsend(ledPin);
    ac = new IRTcl112Ac(ledPin);
}

uint32_t transalteCode(String& code)
{
    return strtoul(code.c_str(), NULL, 10);
}

void IRmanager::sendRaw(String& rawData)
{
    ir -> sendNEC(transalteCode(rawData));
}

void IRmanager::sendACdata(ACdata& acData)
{
    ac -> setPower(acData.power);
    ac -> setMode(acData.mode);
    ac -> setTemp(acData.temp);
    ac -> setFan(acData.fan);
    ac -> setEcono(acData.eco);
    ac -> setHealth(acData.health);
    ac -> setLight(acData.light);
    ac -> setTurbo(acData.turbo);
    ac -> setSwingHorizontal(acData.horizontalSwing);
    ac -> setSwingVertical(acData.verticalSwing);
    ir -> sendRaw(controlData, 228, 38);
    delay(200);
    ac -> begin();
    ac -> send();
}