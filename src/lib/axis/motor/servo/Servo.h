// -----------------------------------------------------------------------------------
// axis servo motor
#pragma once
#include "../../../../Common.h"

#ifdef SERVO_MOTOR_PRESENT

#include "../../../encoder/bissc/As37h39bb.h"
#include "../../../encoder/bissc/Jtw24.h"
#include "../../../encoder/cwCcw/CwCcw.h"
#include "../../../encoder/pulseDir/PulseDir.h"
#include "../../../encoder/pulseOnly/PulseOnly.h"
#include "../../../encoder/quadrature/Quadrature.h"
#include "../../../encoder/quadratureEsp32/QuadratureEsp32.h"
#include "../../../encoder/serialBridge/SerialBridge.h"

#include "dc/Dc.h"
#include "tmc2209/Tmc2209.h"
#include "tmc5160/Tmc5160.h"

#include "feedback/Pid/Pid.h"

#ifndef SERVO_SLEW_DIRECT
  #define SERVO_SLEW_DIRECT OFF
#endif

#ifndef SERVO_SLEWING_TO_TRACKING_DELAY
  #define SERVO_SLEWING_TO_TRACKING_DELAY 3000 // in milliseconds
#endif

class ServoMotor : public Motor {
  public:
    // constructor
    ServoMotor(uint8_t axisNumber, ServoDriver *Driver, Encoder *encoder, uint32_t encoderOrigin, bool encoderReverse, Feedback *feedback, ServoControl *control, long syncThreshold, bool useFastHardwareTimers = true);

    // sets up the servo motor
    bool init();

    // set motor reverse state
    void setReverse(int8_t state);

    // get driver type code
    inline char getParameterTypeCode() { return feedback->getParameterTypeCode(); }

    // set motor parameters
    void setParameters(float param1, float param2, float param3, float param4, float param5, float param6);

    // validate motor parameters
    bool validateParameters(float param1, float param2, float param3, float param4, float param5, float param6);

    // sets motor enable on/off (if possible)
    void enable(bool value);

    // get the associated motor driver status
    DriverStatus getDriverStatus();

    // resets motor and target angular position in steps, also zeros backlash and index 
    void resetPositionSteps(long value);

    // get instrument coordinate, in steps
    long getInstrumentCoordinateSteps();

    // set instrument coordinate, in steps
    void setInstrumentCoordinateSteps(long value);

    // distance to target in steps (+/-)
    long getTargetDistanceSteps();

    // get tracking mode steps per slewing mode step
    inline int getStepsPerStepSlewing() { return 64; }

    // get movement frequency in steps per second
    float getFrequencySteps();

    // set frequency (+/-) in steps per second negative frequencies move reverse in direction (0 stops motion)
    void setFrequencySteps(float frequency);

    // set slewing state (hint that we are about to slew or are done slewing)
    void setSlewing(bool state);

    // get encoder count
    int32_t getEncoderCount() { return encoder->count; }

    // updates PID and sets servo motor power/direction
    void poll();

    // sets dir as required and moves coord toward target at setFrequencySteps() rate
    void move();
    
    // calibrate the motor driver
    void calibrateDriver() { driver->calibrateDriver(); }

    // set zero of absolute encoders
    uint32_t encoderZero();

    // set origin of absolute encoders
    void encoderSetOrigin(uint32_t origin) { encoder->setOrigin(origin); }

    // read encoder
    int32_t encoderRead();

    // servo motor driver
    ServoDriver *driver;

    // servo encoder
    Encoder *encoder;

    float velocityPercent = 0.0F;
    long delta = 0;

  private:
    float velocityEstimate = 0.0F;
    float velocityOverride = 0.0F;

    long encoderApplyFilter(long encoderCounts);

    uint8_t servoMonitorHandle = 0;
    uint8_t taskHandle = 0;
    float maxFrequency = HAL_FRACTIONAL_SEC; // fastest timer rate

    int  stepSize = 1;                  // step size
    volatile int  homeSteps = 1;        // step count for microstep sequence between home positions (driver indexer)
    volatile bool takeStep = false;     // should we take a step

    float currentFrequency = 0.0F;      // last frequency set 
    float lastFrequency = 0.0F;         // last frequency requested
    unsigned long lastPeriod = 0;       // last timer period (in sub-micros)
    long syncThreshold = OFF;           // sync threshold in counts (for absolute encoders) or OFF

    long lastEncoderCounts = 0;         // the last encoder position for stall check
    unsigned long lastCheckTime = 0;    // time since the last encoder position was checked
    unsigned long startTime = 0;        // time at start of servo polling
    unsigned long lastSlewingTime = 0;  // time when last slewing

    volatile int absStep = 1;           // absolute step size (unsigned)
    volatile long originIndexSteps = 0; // for absolute motor position to axis position at coordinate origin

    void (*callback)() = NULL;

    Feedback *feedback;
    ServoControl *control;

    bool useFastHardwareTimers = true;
    bool slewing = false;
    bool motorStepsInitDone = false;
    bool homeSet = false;
    bool encoderReverse = false;
    bool encoderReverseDefault = false;
    bool wasAbove33 = false;
    bool wasBelow33 = false;
    long lastTargetDistance = 0;
};

#endif