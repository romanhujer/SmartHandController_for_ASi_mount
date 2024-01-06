// -----------------------------------------------------------------------------------
// axis servo TMC5160 stepper motor driver
#pragma once

#include <Arduino.h>
#include "../../../../../Common.h"

#ifdef SERVO_TMC5160_PRESENT

#include "../ServoDriver.h"

#ifndef DRIVER_TMC_STEPPER_AUTOGRAD
  #define DRIVER_TMC_STEPPER_AUTOGRAD true
#endif

#include <TMCStepper.h> // https://github.com/teemuatlut/TMCStepper

typedef struct ServoTmcSpiPins {
  int16_t step;
  int16_t dir;
  int16_t enable;
  uint8_t enabledState;
  int16_t m0;
  int16_t m1;
  int16_t m2;
  int16_t m3;
  int16_t fault;
} ServoTmcPins;

typedef struct ServoTmcSettings {
  int16_t model;
  int8_t  status;
  int32_t velocityMax;   // maximum velocity in steps/second
  int32_t acceleration;  // acceleration steps/second/second
  int16_t microsteps;
  int16_t current;
} ServoTmcSettings;

class ServoTmc5160 : public ServoDriver {
  public:
    // constructor
    ServoTmc5160(uint8_t axisNumber, const ServoTmcPins *Pins, const ServoTmcSettings *TmcSettings);

    // decodes driver model and sets up the pin modes
    void init();

    // enable or disable the driver using the enable pin or other method
    void enable(bool state);

    // power level to the motor
    float setMotorVelocity(float power);

    // update status info. for driver
    void updateStatus();

    // calibrate the motor if required
    void calibrateDriver();

    const ServoTmcSettings *Settings;

  private:
    float rSense = 0.075F;

    bool stealthChop() { 
      if ((axisNumber == 1 && AXIS1_DRIVER_DECAY == AXIS1_DRIVER_DECAY_GOTO && AXIS1_DRIVER_DECAY == STEALTHCHOP) ||
         (axisNumber == 2 && AXIS2_DRIVER_DECAY == AXIS2_DRIVER_DECAY_GOTO && AXIS2_DRIVER_DECAY == STEALTHCHOP)) return true; else return false;
    }

    #if SERIAL_TMC == SoftSerial
      SoftwareSerial SerialTMC;
    #endif

    TMC5160Stepper *driver;

    int16_t currentRms;
    bool powered = false;
    float currentVelocity = 0.0F;
    float acceleration;
    float accelerationFs;
    const ServoTmcSpiPins *Pins;
};

#endif
