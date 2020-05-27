#include <ESP8266WiFi.h>
#include <MQTTClient.h>
const char* ssid= "zam";
const char* password= "12345678";

WiFiClient WiFiclient;
MQTTClient client;

unsigned long lastMillis = 0;

void setup() {
Serial.begin(115200);
delay(10);
Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
  }
Serial.println("WiFi connected");Serial.println("IP address: ");
Serial.println(WiFi.localIP());
delay(2000);
  
Serial.print("connecting to MQTT broker...");
client.begin("broker.shiftr.io", WiFiclient);
  connect();
}

void connect() {
 while (!client.connect("nodemcu", "try", "try")) {
Serial.print(".");
  }
Serial.println("\nconnected!");
  client.subscribe("nodemcu");
}

void loop() {
  int val = analogRead(A0);
  client.loop();
  if(!client.connected()) {
 connect();
  }
}

void messageReceived(String topic, String payload, char * bytes, unsigned int length) {
Serial.print("incoming: ");
Serial.print(topic);
  
Serial.print(" - ");
Serial.print(payload);
Serial.println();
}
