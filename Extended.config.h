// ---------------------------------------------------------------------------------------------------------------------------------
// Configuration for OnStep SmartHandServer infrequently used eXtended options

//                                 *** Most users will not change anything in this file! ***

// ---------------------------------------------------------------------------------------------------------------------------------
// ADJUST THE FOLLOWING TO CONFIGURE YOUR CONTROLLER FEATURES ----------------------------------------------------------------------
// <-Req'd = always must set, <-Often = usually must set, Option = optional, Adjust = adjust as req'd, Infreq = infrequently changed

// DEBUG ------------------------------------------------------------ see https://onstep.groups.io/g/main/wiki/6-Configuration#DEBUG
// Enable additional debugging and/or status messages on the specified SERIAL_DEBUG port
// Note that the SERIAL_DEBUG port cannot be used for normal communication with OnStep

//      Parameter Name              Value        Default  Notes                                                                 Hint
#define DEBUG                    VERBOSE  //         OFF, Use ON for background error messages only, use VERBOSE for all      Infreq
                                          //              error and status messages, use PROFILER for VT100 task profiler,
                                          //              use REMOTE to forward verbose debug output to OnStep
#define SERIAL_DEBUG               Serial //      Serial, Or use any h/w serial port. Serial1 or Serial2, etc. as supported.  Option
#define SERIAL_DEBUG_BAUD            9600 //        9600, n. Where n=9600,19200,57600,115200 (common baud rates.)             Option

// NON-VOLATILE STORAGE ------------------------------------------------------------------------------------------------------------
#define NV_WIPE                       OFF //         OFF, Causes the defaults to be written back into NV (FLASH,EEPROM,etc.)  Infreq
                                          //              ***     IMPORTANT: ENABLE THIS OPTION THEN UPLOAD, WAIT A MINUTE    ***
// Warning --->                           //              ***     OR TWO THEN SET THIS OPTION TO OFF AND UPLOAD AGAIN.        ***
                                          //              ***     LEAVING THIS OPTION ENABLED CAN CAUSE EXCESSIVE NV          ***
                                          //              ***     WEAR AND DAMAGE THE MICROCONTROLLER NV SUBSYSTEM !!!        ***

#define SERIAL_IP_MODE      STATION //     STATION //STATION // OFF //         OFF, Use STATION to enable the interface (ESP32 only.)                   Option
// IP ADDRESS SETTINGS -------------------------------------------------------------------------------------------------------------
                                          //              then specify SERIAL_IP as the serial port in Config.h

#define ONSTEP1_HOST_NAME      "AM5" //    "OnStep", Wifi Host Name to connnect to, leave blank to disable.              Adjust
#define ONSTEP1_SSID           "AMH_0fb340" //    "ONSTEP", Wifi alternate Station SSID to connnect to.                         Adjust  
#define ONSTEP1_PASSWORD       "12345678" //  "password", Wifi Station mode password.                                         Adjust
#define ONSTEP1_IP_ADDR     {192,168,4,1} //  ..168,0,1}, Wifi Target IP Address to connect to.                               Adjust

#define ONSTEP2_HOST_NAME      "" //          "", Wifi Host Name to connnect to, leave blank to disable.              Adjust
#define ONSTEP2_SSID           "AM3" //    "ONSTEP", Wifi alternate Station SSID to connnect to.                         Adjust
#define ONSTEP2_PASSWORD       "12345678" //          "", Wifi alternate Station mode password.                               Adjust
#define ONSTEP2_IP_ADDR     {192,168,4,1} //  ..168,0,1}, Wifi alternate Target IP Address to connect to.                     Adjust

#define ONSTEP3_HOST_NAME      "" //          "", Wifi Host Name to connnect to, leave blank to disable.              Adjust
#define ONSTEP3_SSID           "ASIAIR" //    "ONSTEP", Wifi alternate Station SSID to connnect to.                         Adjust
#define ONSTEP3_PASSWORD       "12345678" //  "password", Wifi alternate Station mode password.                               Adjust
#define ONSTEP3_IP_ADDR     {10,0,0,1} //  ..168,0,1}, Wifi alternate Target IP Address to connect to.                     Adjust
