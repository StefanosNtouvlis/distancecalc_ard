#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

// Use pins 2 and 3 to communicate with DFPlayer Mini
static const uint8_t PIN_MP3_TX = 2; // Connects to module's RX
static const uint8_t PIN_MP3_RX = 3; // Connects to module's TX
static const uint8_t TRIG_PIN = 4;   // Connects to ultrasonic sensor's trig pin
static const uint8_t ECHO_PIN = 5;   // Connects to ultrasonic sensor's echo pin
const int MAX_RANGE = 200; // Set the maximum range threshold (in centimeters)


SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);

// Create the Player object
DFRobotDFPlayerMini player;
int distance;

  int calculateDistance()
{
  // Trigger ultrasonic sensor to send a pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  // Measure the duration of the pulse sent by the ultrasonic sensor
  unsigned long duration = pulseIn(ECHO_PIN, HIGH);
  // Calculate the distance in centimeters
     distance = duration * 0.034 / 2;
    return distance;
}

void setup() {
  // Init USB serial port for debugging
  Serial.begin(9600);
  // Init serial port for DFPlayer Mini
  softwareSerial.begin(9600);

  // Start communication with DFPlayer Mini
  if (player.begin(softwareSerial)) {
    Serial.println("OK");
    // Set volume to maximum (0 to 30).
    player.volume(30);
  } else {
    Serial.println("Connecting to DFPlayer Mini failed!");
  }
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {

  calculateDistance();
  // Check if an object is within range (e.g., less than 100cm)
  if (distance > 0 && distance < 17) { 
      Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
    player.play(1);
    Serial.println("Object within 1st range. Playing audio.");
    delay(5000); // Delay to avoid repetitive triggering
  }
}

