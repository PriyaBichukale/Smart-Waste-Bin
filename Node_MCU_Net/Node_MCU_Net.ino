#include <ESP8266WiFi.h>
#include <WiFiClient.h>
const char* ssid = "Priya"; // Enter your WiFi SSID
const char* password = "Priya123"; // Enter your WiFi password
const char* host = "api.thingspeak.com"; // ThingHTTP host address
const int httpPort = 80; // Port to connect to ThingHTTP
const char* apiKey = "LKSH9R42EJ6OB6S3"; // ThingHTTP API key
const int minDistance = 0; // Minimum distance
const int maxDistance = 22; // Maximum distance
void setup() {
Serial.begin(9600); // Initialize serial communication with Arduino
delay(1000); // Wait for Arduino to start up
// Connect to WiFi network
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");
Serial.println("IP address: ");
Serial.println(WiFi.localIP());
}
void loop() {
// Check for message from Arduino
if (Serial.available() > 0) {
// Read distance value from Arduino
String distanceStr = Serial.readStringUntil('\n');
int distance = distanceStr.toInt();
// Calculate fill level percentage based on distance
int fillLevelPercentage = map(distance, minDistance, maxDistance, 100, 1);
// Print the fill level percentage
Serial.print("Dustbin fill level: ");
Serial.print(fillLevelPercentage);
Serial.println("%");
// Send HTTP request to ThingHTTP if distance is below or equal to 3 cm
if (distance == 3) {
sendHTTPRequest();
}
}
}
void sendHTTPRequest() {
// Use WiFiClient class to create TCP connections
WiFiClient client;
if (!client.connect(host, httpPort)) {
Serial.println("Connection failed");
return;
}

// Send HTTP request to ThingHTTP
client.print(String("GET /apps/thinghttp/send_request?api_key=") + apiKey + " HTTP/1.1\r\n" +
"Host: " + host + "\r\n" +
"Connection: close\r\n\r\n");
// Wait for the response
delay(500);
while (client.available()) {
String line = client.readStringUntil('\r');
Serial.print(line);
}
Serial.println();
Serial.println("Request sent to ThingHTTP");
}