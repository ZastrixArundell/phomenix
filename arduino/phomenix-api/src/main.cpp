#include <ESP8266WiFi.h>
#include <Config.h>
#include <PhoenixConnection.hpp>

// Values specific to the WiFi connection
const char* ssid     = SSID;
const char* password = PASSWORD;

// Values specific to the WebSocket connection
const char* deviceId     = DEVICE_ID;
const char* deviceName   = DEVICE_NAME;
const char* websocketUrl = WEBSOCKET_URL;
const char* origin       = ORIGIN;

PhoenixConnection connection(deviceId, deviceName, websocketUrl, origin);

// Toggle whether you want to use custom callbacks or the default
#define CUSTOM true

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

	#if CUSTOM == true
		connection.setMessageCallback([](WebsocketsMessage message){
			Serial.print("Hey, I got a new message: ");
			Serial.println(message.data());
		}).setJoinCallback([](){
			Serial.print("So I just joined a new websocket channel with the name of: ");
			Serial.println(deviceName);
		}).setLeaveCallback([](){
			Serial.println("Well, looks like I left!");
		});
	#endif
	
	connection.connect().join();
}

void loop()
{
  connection.poll();
  connection.sendHeartbeat();
}
