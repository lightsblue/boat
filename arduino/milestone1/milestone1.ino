/*
  Milestone 1 PWM + OLED status display

  PWM (Pulse-Width Modulation) is a way to simulate an analog voltage
  by switching a digital pin on and off at a fixed frequency. The
  “duty cycle” (ratio of on-time to total period) sets the effective
  power. For example, at 50% duty on a 3.3 V ESP32 pin you get ~1.65 V.

  We use PWM here to drive the ESC signal pins: they expect a pulse
  train (typically 50 Hz–400 Hz on RC gear, but many ESCs work up to
  1 kHz). By changing duty you change motor throttle.
*/

#include <Wire.h>
#include "HT_SSD1306Wire.h"    // Heltec SSD1306 driver
#include "HT_DisplayUi.h"      // UI framework for Heltec OLED

// === PWM settings ===
const int      pinA    = 4;      // GPIO4 → ESC 1 signal
const int      pinB    = 5;      // GPIO5 → ESC 2 signal
const uint32_t pwmFreq = 1000;   // 1 kHz PWM frequency
const uint8_t  pwmRes  = 8;      // 8-bit resolution (0–255 duty values)
const int      dutyA   = 128;    // 128/255 ≈ 50% duty cycle
const int      dutyB   =  64;    // 64/255 ≈ 25% duty cycle

// === OLED wiring & setup ===
#ifdef WIRELESS_STICK_V3
  // V3 board: 64×32 display
  static SSD1306Wire display(0x3c, 500000, SDA_OLED, SCL_OLED, GEOMETRY_64_32, RST_OLED);
#else
  // Non-V3 board: 128×64 display
  static SSD1306Wire display(0x3c, 500000, SDA_OLED, SCL_OLED, GEOMETRY_128_64, RST_OLED);
#endif

DisplayUi ui(&display);          // UI controller

// === Overlay function: runs on top of every frame ===
void msOverlay(ScreenDisplay* dsp, DisplayUiState* state) {
  dsp->setTextAlignment(TEXT_ALIGN_RIGHT);
  dsp->setFont(ArialMT_Plain_10);

  // top-right corner: uptime in milliseconds
  dsp->drawString(display.width()-1,  0, String(millis()));

  // below that: show each PWM duty value
  dsp->drawString(display.width()-1, 10, "A:" + String(dutyA));
  dsp->drawString(display.width()-1, 20, "B:" + String(dutyB));
}

// placeholder frame callbacks
void drawFrame1(ScreenDisplay* dsp, DisplayUiState* st, int16_t x, int16_t y) { }
void drawFrame2(ScreenDisplay* dsp, DisplayUiState* st, int16_t x, int16_t y) { }
void drawFrame3(ScreenDisplay* dsp, DisplayUiState* st, int16_t x, int16_t y) { }
void drawFrame4(ScreenDisplay* dsp, DisplayUiState* st, int16_t x, int16_t y) { }
void drawFrame5(ScreenDisplay* dsp, DisplayUiState* st, int16_t x, int16_t y) { }

// array of frame callbacks (empty, but required by the UI)
FrameCallback  frames[]    = { drawFrame1, drawFrame2, drawFrame3, drawFrame4, drawFrame5 };
const int      frameCount  = sizeof(frames) / sizeof(frames[0]);
OverlayCallback overlays[] = { msOverlay };
const int      overlaysCount = sizeof(overlays) / sizeof(overlays[0]);

// control pin for powering the OLED (per Heltec hardware design)
void VextON()  { pinMode(Vext, OUTPUT); digitalWrite(Vext, LOW);  }
void VextOFF() { pinMode(Vext, OUTPUT); digitalWrite(Vext, HIGH); }

void setup() {
  Serial.begin(115200);
  
  // turn on OLED power rail (Vext pin)
  VextON();
  delay(100);

  // === configure PWM outputs ===
  // set frequency, resolution, then initial duty
  analogWriteFrequency(pinA, pwmFreq);
  analogWriteResolution(pinA, pwmRes);
  analogWriteFrequency(pinB, pwmFreq);
  analogWriteResolution(pinB, pwmRes);

  // send PWM to ESCs (they’ll arm and beep)
  analogWrite(pinA, dutyA);
  analogWrite(pinB, dutyB);

  // === initialize the display + UI ===
  ui.setTargetFPS(30);                    // update UI at 30 frames/sec
  ui.setFrames(frames, frameCount);       // supply our (empty) frames
  ui.setOverlays(overlays, overlaysCount);// supply our overlay
  ui.init();                              // OLED power-up + start animation
}

void loop() {
  // drive the UI state machine; returns leftover time
  int timeLeft = ui.update();
  if (timeLeft > 0) {
    delay(timeLeft);  // avoid burning CPU
  }
}
