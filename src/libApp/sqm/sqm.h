// -----------------------------------------------------------------------------------------------------------------------------
// SQM related functions
#pragma once

#include "../../Common.h"

enum SQMSensor: uint8_t { SQMS_NONE, SQMS_TSL2591};

class SQM {
  public:
    bool init();

    // designed for a 2s polling interval
    void poll();
    // get SQM in mas
    float getSQM();
    // set temperature in deg. C
    bool setTemperature(float t);
   
        
  private:
    SQMSensor sqmSensor = SQMS_NONE;
    bool success = false;
    bool active = false;
    float sTemperature = NAN;
    double mag = NAN;
    float averageMag = NAN;  
    float last_mag_per_sq_arcsec = NAN;
    unsigned long last_mag_per_sq_arcsec_time = 0;
};

extern SQM sqm;
