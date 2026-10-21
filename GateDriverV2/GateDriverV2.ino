#include <Arduino.h>
#include "lib/IO/io.h"
#include "lib/StatusBlink/StatusBlink.h"
#include "lib/PWM/PWM.h"

#define R_PWM   38
#define L_PWM   41
#define PWM_EN  40
#define STATUS_LED_PIN 14

IO pwmEnable(PWM_EN, IO_OUTPUT, ACTIVE_HIGH);
StatusBlink statusLed;
PWM lpwm(L_PWM, 20000, 8);
PWM rpwm(R_PWM, 20000, 8);

void setup() 
{
  statusLed.begin(STATUS_LED_PIN, 200000);  // Toggle every blink() call.
  statusLed.off();

  pwmEnable.begin();
  pwmEnable.off();  // Disable PWM while configuring the outputs.

  lpwm.begin();
  rpwm.begin();
  lpwm.off();
  rpwm.off();
  lpwm.enable();
  rpwm.enable();


  pwmEnable.on();  // Use pwmEnable.off() to disable PWM.
}

void loop() {
  statusLed.blink();

  // Forward: right PWM at 20%, left PWM off.
  lpwm.off();
  rpwm.setDuty(20);
  delay(2000);

  // Reverse: turn off right PWM before driving left PWM.
  rpwm.off();
  lpwm.setDuty(20);
  delay(2000);
}
// // YD-ESP32-S3-N16R8 onboard WS2812 (NeoPixel) data pin.
// constexpr uint8_t RGB_LED_PIN = 48;
// constexpr uint8_t LED_BRIGHTNESS = 32;  // 0-255
// constexpr unsigned long BLINK_INTERVAL_MS = 500;

// void setup() {
//   rgbLedWrite(RGB_LED_PIN, 0, 0, 0);
// }

// void loop() {
//   rgbLedWrite(RGB_LED_PIN, LED_BRIGHTNESS, 0, 0);  // Red
//   delay(BLINK_INTERVAL_MS);
//   rgbLedWrite(RGB_LED_PIN, 0, 0, 0);
//   delay(BLINK_INTERVAL_MS);

//   rgbLedWrite(RGB_LED_PIN, 0, LED_BRIGHTNESS, 0);  // Green
//   delay(BLINK_INTERVAL_MS);
//   rgbLedWrite(RGB_LED_PIN, 0, 0, 0);
//   delay(BLINK_INTERVAL_MS);

//   rgbLedWrite(RGB_LED_PIN, 0, 0, LED_BRIGHTNESS);  // Blue
//   delay(BLINK_INTERVAL_MS);
//   rgbLedWrite(RGB_LED_PIN, 0, 0, 0);
//   delay(BLINK_INTERVAL_MS);
// }
