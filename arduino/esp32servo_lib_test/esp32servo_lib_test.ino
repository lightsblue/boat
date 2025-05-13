#include <ESP32Servo.h>

Servo esc1;
Servo esc2;

const int esc1Pin = 4;
const int esc2Pin = 6;
const int minPulse = 1000;
const int maxPulse = 2000;
const int sweepStep = 10;
const int sweepDelay = 50; // ms

void setup() {
  Serial.begin(115200);
  esc1.setPeriodHertz(50); // Standard 50 Hz for ESC/servo
  esc2.setPeriodHertz(50);
  esc1.attach(esc1Pin, minPulse, maxPulse); // Attach to GPIO4, 1000-2000us pulse
  esc2.attach(esc2Pin, minPulse, maxPulse); // Attach to GPIO6, 1000-2000us pulse
  Serial.println("Arming ESCs at zero throttle...");
  esc1.writeMicroseconds(minPulse); // Arm at zero throttle
  esc2.writeMicroseconds(minPulse);
  delay(2000);
  Serial.println("Armed. Beginning ramp test.");
}

void loop() {
  // Ramp up
  Serial.println("Ramping up throttle...");
  for (int p = minPulse; p <= maxPulse; p += sweepStep) {
    esc1.writeMicroseconds(p);
    esc2.writeMicroseconds(p);
    Serial.print("Throttle: ");
    Serial.print(p);
    Serial.println(" us");
    delay(sweepDelay);
  }
  // Ramp down
  Serial.println("Ramping down throttle...");
  for (int p = maxPulse; p >= minPulse; p -= sweepStep) {
    esc1.writeMicroseconds(p);
    esc2.writeMicroseconds(p);
    Serial.print("Throttle: ");
    Serial.print(p);
    Serial.println(" us");
    delay(sweepDelay);
  }
  // Off for 2 seconds
  Serial.println("Throttle off (1000us) for 2 seconds...");
  esc1.writeMicroseconds(minPulse);
  esc2.writeMicroseconds(minPulse);
  delay(2000);
}
