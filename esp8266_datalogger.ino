#include <ESP8266WiFi.h>

const char* ssid = "rezwan";
const char* password = "1234567890";

const char* host = "api.thingspeak.com";

void setup() {

	Serial.begin(115200);
	delay(10);

	// Connect to a WiFi network

	Serial.print("Connecting to ");
	Serial.println(ssid);

	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}

	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());

}


void loop() {

	WiFiClient client;
	const int httpPort = 80;

	if (!client.connect(host, httpPort)) {
		Serial.println("connection failed");
		return;
	}
	else
	{
		Serial.println("connected !");
	}


	//client.print("GET /update?key=82RS9VJ7YHQGMWT1&field1=1000\n");

	char buffer[200];
	int adcValue = analogRead(A0);
	Serial.println(adcValue);
	sprintf(buffer, "GET /update?key=82RS9VJ7YHQGMWT1&field1=%d\n", adcValue);
	client.print(buffer);

	while (client.available()) {
		String line = client.readStringUntil('\r');
		Serial.print(line);
	}

	client.stop();
	Serial.println("closing connection");

	delay(60000);
}
