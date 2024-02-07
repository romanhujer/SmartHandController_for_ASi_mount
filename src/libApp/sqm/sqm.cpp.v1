// -----------------------------------------------------------------------------------------------------------------------------
// Sky Quality (SQM) related functions

#include "sqm.h"

#include "../../lib/tasks/OnTask.h"

#define LOWSCALE 1.0
#define MEDSCALE 25.0
#define HIGHSCALE 428.0
#define MAXSCALE 9876.0


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
         tsl.setGain(TSL2591_GAIN_MAX);
         tsl.setTiming(TSL2591_INTEGRATIONTIME_600MS);
        //tsl.setGain(TSL2591_GAIN_MED);                   // 1x _LOW, 25x _MED, 428x _HIGH, 9876x _MAX (higher gain = more sensitivity)
        //tsl.setTiming(TSL2591_INTEGRATIONTIME_300MS);    // _100MS, _200MS, _300MS, _400MS, _500MS, _600MS (higher integration time = more sensitivity)
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
      VF("MSG: SQM, start SQM monitor task (rate 5000ms priority 7)... ");
      if (tasks.add(5000, 0, true, 7, sqmPollWrapper, "SQMPoll")) { VLF("success"); } else { VLF("FAILED!"); }
  
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
      if ((long)((last_mag_per_sq_arcsec_time + 60000UL) - millis()) < 0) last_mag_per_sq_arcsec = NAN;

      // read data from TSL2591 (non-blocking)
      uint32_t lum;
      double gainscale = MAXSCALE;
//      tsl.getFullLuminosity(TSL2591_GFL_INIT);
      tsl.getFullLuminosity();
      tasks.yield(500);
      tsl.setGain(TSL2591_GAIN_HIGH);
//      while ( tsl.getFullLuminosity(TSL2591_GFL_WAIT) ) tasks.yield(500);
//      tsl.getFullLuminosity(TSL2591_GFL_WAIT);
//      tsl.getFullLuminosity();
      tasks.yield(500);
//      lum = tsl.getFullLuminosity(TSL2591_GFL_DONE);
      lum = tsl.getFullLuminosity();
      uint16_t ir = lum >> 16;
      uint16_t full = lum & 0xFFFF;
      VLF("MSG: SQM.poll(), GAIN MAX");
      uint16_t visible = full - ir;
 
// automatically adapt gain and integration time
#if 1
      if (visible== 0xFFFF||ir==0xFFFF) {
          tsl.setGain(TSL2591_GAIN_HIGH);
//          tsl.getFullLuminosity();  
          tasks.yield(500);
          lum = tsl.getFullLuminosity();
          ir = lum >> 16;
          full = lum & 0xFFFF;
          VLF("MSG: SQM.poll(), GAIN HIGH");
          if (visible == 0xFFFF || ir == 0xFFFF) { // look, dude. It's daylight at this point. Knock it off
              tsl.setGain(TSL2591_GAIN_MED);
              gainscale = MEDSCALE;
//              tsl.getFullLuminosity();
              tasks.yield(500);
              lum = tsl.getFullLuminosity();
              ir = lum >> 16;
              full = lum & 0xFFFF;
              VLF("MSG: SQM.poll(), GAIN MED");
              if (visible == 0xFFFF || ir == 0xFFFF) { // ARE YOU ON THE SUN?
                tsl.setGain(TSL2591_GAIN_LOW);
                gainscale = LOWSCALE;
//                tsl.getFullLuminosity();
                tasks.yield(500);
                lum = tsl.getFullLuminosity();
                ir = lum >> 16;
                full = lum & 0xFFFF;
                VLF("MSG: SQM.poll(), GAIN LOW");
              }
          }  
      }

//       if (!tsl.autoscale(full, ir)) { mag = NAN; VF("MSG: SQM.poll(), NAN ") ; return; }
#endif      
  
      // correct for sensor temperature sensitivity
#if  SKY_TEMPERATURE != OFF       
      float t = sTemperature;
      if (!isnan(t)) {
         VLF("MSG: SQM.poll(), correct temeperature");
         // Correct fuul (IR+Visible) for ambient temperature effects
         full  =  full * (0.975 + t * 0.00085);  // typical values for intercept and slope according to datasheet
         // Correct ir for ambient temperature effects
         ir =  ir * (  1.05 + t * -0.0019);  // typical values for intercept and slope according to datasheet
      }
#endif             
       // finally get the visible brightness in Lux
      float lux = tsl.calculateLux(full, ir);

      // Lux = Candela at 1 meter.
      // At 1 meter a 1 meter^2 surface has an approximately 60 deg fov so this TSL2591 effectively measures in Candela given a 60 deg TFOV lens.
      // Its sensitivity spread across the 180 deg FOV seems to be about right for 1 Candela with no lens, but I'm not an expert on this!
      // If using a 30 deg TFOV lens, for example, set WEATHER_SKY_QUAL_SCALE 4.0 since light from a smaller surface area is projected onto the sensor.
      float mag_per_sq_arcsec = 0;
      if (lux > 0) { mag_per_sq_arcsec= SKY_QUAL_ZERO + log10((lux * SKY_QUAL_SCALE)/108000.0)/-0.4;}
      else  mag_per_sq_arcsec = 25;
       VF("MSG: SQM.poll(), Mag "); VL(mag_per_sq_arcsec);


#if 0      
      visible = full - ir;    
      double adjustedIR = (float)ir / gainscale;
      double adjustedVisible = (float)visible / gainscale;
      float mag_per_sq_arcsec = 0;

      if (adjustedVisible >0) { mag_per_sq_arcsec = -1.085736205*log(.925925925 * pow(10,-5.)*adjustedVisible);}
      else mag_per_sq_arcsec = 25;
      VF("MSG: SQM.poll(), Mag "); VL(mag_per_sq_arcsec);
#endif



      if (isinf(mag_per_sq_arcsec)) {
         mag_per_sq_arcsec = 25;
      }
      
      last_mag_per_sq_arcsec = mag_per_sq_arcsec;
      last_mag_per_sq_arcsec_time = millis();
      mag  = last_mag_per_sq_arcsec;
   
      // apply a 10 sample rolling average to SQM
      static uint8_t nanCount = 0;
      static bool firstSample = true;
      if (firstSample) {
        firstSample = false;
        averageMag = last_mag_per_sq_arcsec; 
      }

      if (!isnan(mag)) {
        nanCount = 0;
        if  ( last_mag_per_sq_arcsec > 0  && last_mag_per_sq_arcsec < 25  ) { averageMag = (averageMag*9.0 + last_mag_per_sq_arcsec)/10.0; }
      } else {
        if (nanCount < 15) {
          nanCount++;
          VLF("WRN: SQM.poll(), sqm. invalid");
        } else {
          averageMag = 0;
          firstSample = true;
          VLF("WRN: SQM.poll(), ambient sqm. reset");
        }
      }
    }
    #if SQM_SUPRESS_ERRORS == OFF
      else { last_mag_per_sq_arcsec = 0;  }
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

