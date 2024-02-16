// -----------------------------------------------------------------------------------
// Time/Location source DS3231 RTC support
// uses the default I2C port in most cases; though HAL_Wire can redirect to another port (as is done for the Teensy3.5/3.6)
#pragma once

#include "../../Common.h"

typedef struct rtcTimeDate {
  int16_t  year;
  uint8_t  month;
  uint8_t  day;
  uint8_t  hour;
  uint8_t  minute;
  uint8_t  second;
  bool     valid;
} rtcTimeDate;
 
class RealTimeClock {
  public:

    // initialize (also enables the RTC PPS if available)
    bool init();

    // true if date/time ready
    inline bool isReady() { return ready; }

    // set the RTC's time
    void set(int year, int month, int day, int hour, int minute, int second);

 // get the RTC's time

     rtcTimeDate get();

  private:
    bool ready = false;
    rtcTimeDate rt;
};

extern RealTimeClock Rtc;


