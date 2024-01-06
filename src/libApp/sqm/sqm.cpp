// -----------------------------------------------------------------------------------------------------------------------------
// Sky Quality (SQM) related functions

#include "sqm.h"

#include "../../lib/tasks/OnTask.h"

extern bool xBusy;

#if  SKY_QUAL != OFF  
// using customized library from https://github.com/hjd1964/Adafruit_TSL2591_Library 
  #include <Adafruit_TSL2591.h>                                         
  Adafruit_TSL2591 tsl=Adafruit_TSL2591(2591);

#endif

void sqmPollWrapper() { sqm.poll(); }

bool SQM::init() {
  #if SKY_QUAL != OFF
    success = false;
      if (tsl.begin()) { 
         sqmSensor = SQMS_TSL2591; 
//         tsl.setGain(TSL2591_GAIN_MAX);
//         tsl.setTiming(TSL2591_INTEGRATIONTIME_600MS);
         tsl.setGain(TSL2591_GAIN_MED);                   // 1x _LOW, 25x _MED, 428x _HIGH, 9876x _MAX (higher gain = more sensitivity)
         tsl.setTiming(TSL2591_INTEGRATIONTIME_300MS);    // _100MS, _200MS, _300MS, _400MS, _500MS, _600MS (higher integration time = more sensitivity)
        success = true; 
       } 
      else { 
        DLF("WRN: SQM.init(), TSL2591 not found"); 
       }
    
    // follow any I2C device in-library init with a reset of the I2C bus speed
    #ifdef HAL_WIRE_RESET_AFTER_CONNECT
        HAL_Wire.end();
        HAL_Wire.begin();
    #endif
        HAL_Wire.setClock(HAL_WIRE_CLOCK);

    if (success) {
      VF("MSG: SQM, start weather monitor task (rate 5000ms priority 7)... ");
      if (tasks.add(1000, 0, true, 7, sqmPollWrapper, "SQMPoll")) { VLF("success"); } else { VLF("FAILED!"); }
  
    }
  #else
    success = true;
  #endif
  return success;
}

// poll the weather sensor once every 5 seconds
void SQM::poll() {
    if (success && !xBusy) {
      // safe-guard to invalidate stale readings after 30 seconds
      if ((long)((last_mag_per_sq_arcsec_time + 30000UL) - millis()) < 0) last_mag_per_sq_arcsec = NAN;

      // read data from TSL2591 (non-blocking)
      uint32_t lum;

      tsl.getFullLuminosity(TSL2591_GFL_INIT);
      tasks.yield(500);

      while (tsl.getFullLuminosity(TSL2591_GFL_WAIT)) tasks.yield(500);
      tasks.yield(500);
      lum = tsl.getFullLuminosity(TSL2591_GFL_DONE);
   
      uint16_t ir = lum >> 16;
      uint16_t full = lum & 0xFFFF;

      // automatically adapt gain and integration time
      if (!tsl.autoscale(full, ir)) { mag = NAN; return; }
  
      // correct for sensor temperature sensitivity
      float t = sTemperature;
      if (!isnan(t)) {
        full = tsl.temperatureCorrectCh0(t, full);
        ir = tsl.temperatureCorrectCh1(t, ir);
       }

      // finally get the visible brightness in Lux
      float lux = tsl.calculateLux(full, ir);

      // Lux = Candela at 1 meter.
      // At 1 meter a 1 meter^2 surface has an approximately 60 deg fov so this TSL2591 effectively measures in Candela given a 60 deg TFOV lens.
      // Its sensitivity spread across the 180 deg FOV seems to be about right for 1 Candela with no lens, but I'm not an expert on this!
      // If using a 30 deg TFOV lens, for example, set WEATHER_SKY_QUAL_SCALE 4.0 since light from a smaller surface area is projected onto the sensor.
      float mag_per_sq_arcsec = SKY_QUAL_ZERO + log10((lux * SKY_QUAL_SCALE)/108000.0)/-0.4;
      last_mag_per_sq_arcsec = mag_per_sq_arcsec;
      last_mag_per_sq_arcsec_time = millis();
      mag  = last_mag_per_sq_arcsec;
   
      // apply a 10 sample rolling average to SQM
      static uint8_t nanCount = 0;
      static bool firstSample = true;
      if (firstSample) {
        firstSample = false;
        averageMag = mag; 
      }

      if (!isnan(mag)) {
        nanCount = 0;
        averageMag = (averageMag*9.0 + mag)/10.0;
      } else {
        if (nanCount < 15) {
          nanCount++;
          VLF("WRN: SQM.poll(), sqm. invalid");
        } else {
          averageMag = NAN;
          firstSample = true;
          VLF("WRN: SQM.poll(), ambient sqm. reset");
        }
      }
    }
    #if SQM_SUPRESS_ERRORS == OFF
      else { mag = NAN;  }
    #endif
  
}

// get SQM in mas
float SQM::getSQM() {
 VF("MSG: SQM.getSQM()");  VL( averageMag);
  return averageMag;
}

// set temperature in deg. C
bool SQM::setTemperature(float t) {
    if (t >= -100.0 && t < 100.0) {  sTemperature = t;} else return false;
  return true;
}

SQM sqm;
