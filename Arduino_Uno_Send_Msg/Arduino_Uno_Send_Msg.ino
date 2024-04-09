#include <NewPing.h>
#define TRIGGER_PIN 12 // Arduino pin connected to trigger pin on ultrasonic sensor
#define ECHO_PIN 11 // Arduino pin connected to echo pin on ultrasonic sensor
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
void setup() {
Serial.begin(9600); // Open serial monitor at 9600 baud to see ping results.
Serial.println("Arduino connected to ESP8266.");
delay(1000); // Wait for ESP8266 to start up
}
void loop() {
delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
unsigned int distance = uS / US_ROUNDTRIP_CM; // Convert ping time to distance in cm.
// Print distance
Serial.print("Distance: ");
Serial.print(distance); // Print the distance measured by the ultrasonic sensor
Serial.println(" cm");

// Send distance value to ESP8266
Serial.println(distance);
delay(1000); // Wait 1 second between readings
}