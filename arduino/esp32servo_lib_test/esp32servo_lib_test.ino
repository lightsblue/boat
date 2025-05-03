#include <ESP32Servo.h>

// ————— Pin & ESC pulse settings ——————
const int escPin    = 4;     // Signal pin to your ESC
const int minPulse  = 1000;  // μs = full zero/throttle-off
const int maxPulse  = 2000;  // μs = full throttle
const int sweepStep =   10;  // μs increment per loop
const int sweepDelay=   50;  // ms delay between steps

Servo esc;

void setup() {
  Serial.begin(115200);

  // 1) Configure the ESC object
  //    50 Hz = standard RC servo/ESC refresh rate
  esc.setPeriodHertz(50);
  esc.attach(escPin, minPulse, maxPulse);

  // 2) Arm sequence: hold zero throttle for 2s
  Serial.println("Arming ESC at zero throttle…");
  esc.writeMicroseconds(minPulse);
  delay(2000);
  Serial.println("Armed. Beginning throttle sweep.");
}

void loop() {
  // 3a) Ramp up from zero → full
  Serial.println("Ramping up throttle...");
  for (int p = minPulse; p <= maxPulse; p += sweepStep) {
    esc.writeMicroseconds(p);
    Serial.print("Throttle: ");
    Serial.print(p);
    Serial.println(" us");
    delay(sweepDelay);
  }

  // 3b) Ramp down from full → zero
  Serial.println("Ramping down throttle...");
  for (int p = maxPulse; p >= minPulse; p -= sweepStep) {
    esc.writeMicroseconds(p);
    Serial.print("Throttle: ");
    Serial.print(p);
    Serial.println(" us");
    delay(sweepDelay);
  }
}
