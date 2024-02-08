# Wireles Smart Hand Controller for ZWO mount (AM5/AM3)
Mofifikaction from [OnStep Smart Hand Controller](https://github.com/hjd1964/SmartHandController)


NOTE:
! ! !  A L P H A  _  V E R S I O N  _  P A R T I A L L Y _  W O R K I N G_  N O W  ! ! ! 

Currently most things are already working:
- Setting date, time and location
- tracking on and off 
- switching the tracking speed (sideric lunar and solar)
- Setting speed and guiding with cross buttons
- Goto to objects from internal catalogue
- Goto home and parking 

Alignment to stars and sync is not working  now.  :-(






For SQM with TSL2591 sensor need using customized library. Download from  https://github.com/hjd1964/Adafruit_TSL2591_Library 

For SQM V1.0 with TSL2591 sensor need using customized library from https://github.com/hjd1964/Adafruit_TSL2591_Library 

The SHC adds dedicated hand controller functionality to an OnStep or OnStepX telescope controller. 
This firmware is designed to run on ESP32 (recommended) or Teensy3.2 or Teensy4.0 hardware.
It can communicate with OnStep over the ST4 guiding port (which automatically reconfigures itself for synchronous serial communications when it detects an SHC) or over WiFi instead if running on an ESP32 (recommended.)
The SHC hardware provides physical buttons that are easy to work by feel in the dark and an OLED display for convenient telescope control. 

The SHC software was initially based on [Charles Lemaire](https://pixelstelescopes.wordpress.com/)'s [TeenAstro fork](https://groups.io/g/TeenAstro/wiki/home).

# Features
You can review the SHC capabilities in its [User Manual](https://onstep.groups.io/g/main/wiki/28605) Wiki.

# Documentation
You can review recommended hardware and flashing instructions in the [Smart Hand Controller](https://groups.io/g/onstep/wiki/Smart-Hand-Controller) Wiki.

# License
The Smart Hand Controller is open source free software, licensed under the GPL.

See [LICENSE.txt](./LICENSE.txt) file.

# Primary Author
[Howard Dutton](http://www.stellarjourney.com), Charles Lemaire, and [Khalid Baheyeldin](https://baheyeldin.com)
