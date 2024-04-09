#include <Servo.h> //servo library
Servo servo;
int trigPin = 5; // Define pin for trigger signal of ultrasonic sensor
int echoPin = 6; // Define pin for echo signal of ultrasonic sensor
int servoPin = 7; // Define pin for servo motor
int led = 10; // Define pin for LED

long duration, dist, average;
long aver[3]; //array for average

void setup() {
Serial.begin(9600);
servo.attach(servoPin);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(led, OUTPUT); // Defining LED pin
servo.write(0); //close cap on power on
delay(100);
servo.detach();
}

void measure() {
digitalWrite(led, HIGH); // Turning on LED
digitalWrite(trigPin, LOW);
delayMicroseconds(5);
digitalWrite(trigPin, HIGH);
delayMicroseconds(15);
digitalWrite(trigPin, LOW);
pinMode(echoPin, INPUT);
duration = pulseIn(echoPin, HIGH);
dist = (duration/2) / 29.1; //obtain distance
}

void loop() {
for (int i = 0; i <= 2; i++) { //average distance
measure();
aver[i] = dist;
delay(10); //delay between measurements
}
dist = (aver[0] + aver[1] + aver[2]) / 3;

Serial.print("Distance: ");
Serial.print(dist);
Serial.println(" cm");

if (dist < 50) {
// Change distance as per your need
servo.attach(servoPin);
delay(1);
servo.write(90); // Adjusted position to 90 degrees
delay(1000); // Adjusted delay to 1 second (1000 milliseconds)
servo.detach(); // Detach the servo motor
} else {
servo.attach(servoPin); // Attach the servo motor
delay(1);
servo.write(0); // Adjusted position to 0 degrees
delay(1000); // Adjusted delay to 1 second (1000 milliseconds)
servo.detach(); // Detach the servo motor
}
}