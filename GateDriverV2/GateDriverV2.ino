#include <Arduino.h>
#include "lib/IO/io.h"
#include "lib/StatusBlink/StatusBlink.h"
#include "lib/PWM/PWM.h"
#include "lib/RTC/RtcDs3231.h"

#define R_PWM   38
#define L_PWM   41
#define PWM_EN  40
#define STATUS_LED_PIN 14
#define RTC_SDA_PIN 21
#define RTC_SCL_PIN 47
#define BUZZER_PIN 1
#define CALLING_BELL_PIN 2

IO pwmEnable(PWM_EN, IO_OUTPUT, ACTIVE_HIGH);
IO buzzer(BUZZER_PIN, IO_OUTPUT, ACTIVE_HIGH);
IO callingBell(CALLING_BELL_PIN, IO_OUTPUT, ACTIVE_HIGH);
StatusBlink statusLed;
PWM lpwm(L_PWM, 20000, 8);
PWM rpwm(R_PWM, 20000, 8);
RtcDs3231 rtc;

void setup() 
{
  Serial.begin(115200);
  Wire.setPins(RTC_SDA_PIN, RTC_SCL_PIN);
  if (!rtc.begin()) {
    Serial.println("DS3231 initialization failed. Check RTC wiring.");
  } else {
    // Clock-setting firmware: remove this call after setting the RTC,
    // otherwise every restart restores this firmware's build time.
    rtc.setDateTime(DateTime(F(__DATE__), F(__TIME__)));
    Serial.print("RTC date/time set: ");
    Serial.println(rtc.readDateTimeString());
  }

  statusLed.begin(STATUS_LED_PIN, 200000);  // Toggle every blink() call.
  statusLed.off();

  pwmEnable.begin();
  pwmEnable.off();  // Disable PWM while configuring the outputs.

  buzzer.begin();
  callingBell.begin();
  // Test both outputs together once at startup, before enabling the motor.
  buzzer.on();
  callingBell.on();
  delay(500);
  buzzer.off();
  callingBell.off();

  lpwm.begin();
  rpwm.begin();
  lpwm.off();
  rpwm.off();
  lpwm.enable();
  rpwm.enable();


  pwmEnable.on();  // Use pwmEnable.off() to disable PWM.
}

void loop() {


  // 22222 buzzer /calling bell relay..not operate

  //  buzzer.on();
   callingBell.on();
  delay(1000);
  // buzzer.off();
  callingBell.off();
  delay(1000);

  // statusLed.blink();
  // if (rtc.isInitialized()) {
  //   Serial.print("RTC time: ");
  //   Serial.println(rtc.readTimeString());
  // }

  // // Forward: right PWM at 20%, left PWM off.
  // lpwm.off();
  // rpwm.setDuty(20);
  // delay(2000);

  // // Reverse: turn off right PWM before driving left PWM.
  // rpwm.off();
  // lpwm.setDuty(20);
  // delay(2000);
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
