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
    uint8_t nanCount = 0;
    bool firstSample = true;
    float sTemperature = NAN;
    float averageMag = 0;  
  //  float last_mag_per_sq_arcsec = 0;
    float  mag_per_sq_arcsec = 0;
    float mag_measurement_I = 0;
    float mag_measurement_II = 0;
    float mag_measurement_III = 0;
    uint8_t  measurementCount = 0; 
    unsigned long last_mag_per_sq_arcsec_time = 0;
};

extern SQM sqm;
