#include <ESP32Servo.h>

Servo esc;

const int escPin = 4;
const int minPulse = 1000;
const int maxPulse = 2000;
const int sweepStep = 10;
const int sweepDelay = 50; // ms

void setup() {
  Serial.begin(115200);
  esc.setPeriodHertz(50); // Standard 50 Hz for ESC/servo
  esc.attach(escPin, minPulse, maxPulse); // Attach to GPIO4, 1000-2000us pulse
  Serial.println("Arming ESC at zero throttle...");
  esc.writeMicroseconds(minPulse); // Arm at zero throttle
  delay(2000);
  Serial.println("Armed. Beginning ramp test.");
}

void loop() {
  // Ramp up
  Serial.println("Ramping up throttle...");
  for (int p = minPulse; p <= maxPulse; p += sweepStep) {
    esc.writeMicroseconds(p);
    Serial.print("Throttle: ");
    Serial.print(p);
    Serial.println(" us");
    delay(sweepDelay);
  }
  // Ramp down
  Serial.println("Ramping down throttle...");
  for (int p = maxPulse; p >= minPulse; p -= sweepStep) {
    esc.writeMicroseconds(p);
    Serial.print("Throttle: ");
    Serial.print(p);
    Serial.println(" us");
    delay(sweepDelay);
  }
  // Off for 2 seconds
  Serial.println("Throttle off (1000us) for 2 seconds...");
  esc.writeMicroseconds(minPulse);
  delay(2000);
}
