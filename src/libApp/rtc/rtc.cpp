// -----------------------------------------------------------------------------------
// Time/Location source DS3231 RTC support
// uses the default I2C port in most cases; though HAL_Wire can redirect to another port (as is done for the Teensy3.5/3.6)

#include "rtc.h"

#include <Wire.h>
#include <RtcDS3231.h> // https://github.com/Makuna/Rtc/archive/master.zip
RtcDS3231<TwoWire> rtcDS3231(HAL_Wire);

bool RealTimeClock::init() {
  HAL_Wire.begin();
  HAL_Wire.setClock(HAL_WIRE_CLOCK);
  HAL_Wire.beginTransmission(0x68);
  bool error = HAL_Wire.endTransmission() != 0;
  if (!error) {
    rtcDS3231.Begin();
    HAL_Wire.setClock(HAL_WIRE_CLOCK);
    if (!rtcDS3231.GetIsRunning()) rtcDS3231.SetIsRunning(true);

    // see if the RTC is present
    if (rtcDS3231.GetIsRunning()) {
      // frequency 0 (1Hz) on the SQW pin
      rtcDS3231.SetSquareWavePin(DS3231SquareWavePin_ModeClock);
      rtcDS3231.SetSquareWavePinClockFrequency(DS3231SquareWaveClock_1Hz);
      ready = true;
    } else { DLF("WRN: rtc.init(), DS3231 GetIsRunning() false"); }
  } else { DLF("WRN: rtc.init(), DS3231 (I2C 0x68) not found"); }
  #ifdef HAL_WIRE_RESET_AFTER_CONNECT
    HAL_Wire.end();
    HAL_Wire.begin();
    HAL_Wire.setClock(HAL_WIRE_CLOCK);
  #endif
  return ready;
}

void RealTimeClock::set(int year, int month, int day, int hour, int minute, int second) {
  if (!ready) return;
  RtcDateTime updateTime = RtcDateTime(year, month, day, hour, minute, second);
  rtcDS3231.SetDateTime(updateTime);
}

rtcTimeDate RealTimeClock::get() {
  rtcTimeDate rt;
  rt.valid = false;
  if (!ready) { return rt; }
  RtcDateTime now = rtcDS3231.GetDateTime();
  if (now.Year() >= 2018 && now.Year() <= 3000 && now.Month() >= 1 && now.Month() <= 12 && now.Day() >= 1 && now.Day() <= 31 &&
      now.Hour() <= 23 && now.Minute() <= 59 && now.Second() <= 59) {
    rt.year = now.Year(); rt.month = now.Month(); rt.day = now.Day();
    rt.hour = now.Hour(); rt.minute = now.Minute(); rt.second =  now.Second();
    rt.valid = true;    
  }    
  return rt;
}

RealTimeClock Rtc;
