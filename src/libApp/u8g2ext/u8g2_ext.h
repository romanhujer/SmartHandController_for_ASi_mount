#pragma once

#include <U8g2lib.h> // https://github.com/olikraus/u8g2/wiki/u8g2install
#include "u8g2_ext_event.h"

#include "../../Common.h"

class U8G2_EXT : public U8G2
{
public:
  bool UserInterfaceCatalog(KeyPad *extPad, const char *title);
  bool UserInterfaceUserCatalog(KeyPad *extPad, const char *title);
  uint8_t UserInterfaceMessage(KeyPad *extPad, const char *title1, const char *title2, const char *title3, const char *buttons);
#if DISPLAY_WRAP_MENUS == ON
  uint8_t UserInterfaceSelectionList(KeyPad *extPad, const char *title, uint8_t start_pos, const char *sl, bool wrap=true);
#else
  uint8_t UserInterfaceSelectionList(KeyPad *extPad, const char *title, uint8_t start_pos, const char *sl, bool wrap=false);
#endif
  uint8_t UserInterfaceInputValueBoolean(KeyPad *extPad, const char *title, boolean *value);
  uint8_t UserInterfaceInputValueInteger(KeyPad *extPad, const char *title, const char *pre, uint8_t *value, uint8_t lo, uint8_t hi, uint8_t digits, const char *post);
  uint8_t UserInterfaceInputValueFloat(KeyPad *extPad, const char *title, const char *pre, float *value, float lo, float hi, uint8_t len, uint8_t dec, const char *post);
  uint8_t UserInterfaceInputValueDMS(KeyPad *extPad, const char *title, long *value, long lo, long hi, uint8_t digits1, char* symb1, char* symb2, char* symb3, char* symb_plus, char* symb_minus, bool display_seconds);
  uint8_t UserInterfaceInputValueDate(KeyPad *extPad, const char *title, uint8_t& year, uint8_t& month, uint8_t& day);
  uint8_t UserInterfaceInputValueRA(KeyPad *extPad, long *value);
  uint8_t UserInterfaceInputValueDec(KeyPad *extPad, long *value);
  uint8_t UserInterfaceInputValueTime(KeyPad *extPad, long *value, bool hrs24);
  uint8_t UserInterfaceInputValueLatitude(KeyPad *extPad, long *value);
  uint8_t UserInterfaceInputValueLongitude(KeyPad *extPad, long *value);
  uint8_t DrawFwNumeric(uint8_t x, uint8_t y, const char* text);
  uint8_t GetFwNumericWidth(const char* text);
};

class U8G2_EXT_SH1106_128X64_NONAME_1_HW_I2C : public U8G2_EXT {
public: U8G2_EXT_SH1106_128X64_NONAME_1_HW_I2C(const u8g2_cb_t *rotation, uint8_t reset = U8X8_PIN_NONE, uint8_t clock = U8X8_PIN_NONE, uint8_t data = U8X8_PIN_NONE) : U8G2_EXT() {
  u8g2_Setup_sh1106_i2c_128x64_noname_1(&u8g2, rotation, u8x8_byte_arduino_hw_i2c, u8x8_gpio_and_delay_arduino);
  u8x8_SetPin_HW_I2C(getU8x8(), reset, clock, data);
};
};

class U8G2_EXT_SH1106_128X64_NONAME_1_4W_SW_SPI : public U8G2_EXT {
  public: U8G2_EXT_SH1106_128X64_NONAME_1_4W_SW_SPI(const u8g2_cb_t *rotation, uint8_t clock = DISPLAY_SCK_PIN, uint8_t data = DISPLAY_MOSI_PIN, uint8_t cs = DISPLAY_SS_PIN, uint8_t dc = DISPLAY_DC_PIN, uint8_t reset = U8X8_PIN_NONE) : U8G2_EXT() {
    u8g2_Setup_sh1106_128x64_noname_1(&u8g2, rotation, u8x8_byte_arduino_4wire_sw_spi, u8x8_gpio_and_delay_arduino);
    u8x8_SetPin_4Wire_SW_SPI(getU8x8(), clock, data, cs, dc, reset);
  }
};

class U8G2_EXT_SH1106_128X64_NONAME_1_4W_HW_SPI : public U8G2_EXT {
  public: U8G2_EXT_SH1106_128X64_NONAME_1_4W_HW_SPI(const u8g2_cb_t *rotation, uint8_t cs = DISPLAY_SS_PIN, uint8_t dc = DISPLAY_DC_PIN, uint8_t reset = U8X8_PIN_NONE) : U8G2_EXT() {
    u8g2_Setup_sh1106_128x64_noname_1(&u8g2, rotation, u8x8_byte_arduino_hw_spi, u8x8_gpio_and_delay_arduino);
    u8x8_SetPin_4Wire_HW_SPI(getU8x8(), cs, dc, reset);
  }
};

class U8G2_EXT_SSD1306_128X64_NONAME_F_HW_I2C : public U8G2_EXT {
public: U8G2_EXT_SSD1306_128X64_NONAME_F_HW_I2C(const u8g2_cb_t *rotation, uint8_t reset = U8X8_PIN_NONE, uint8_t clock = U8X8_PIN_NONE, uint8_t data = U8X8_PIN_NONE) : U8G2_EXT() {
  u8g2_Setup_ssd1306_i2c_128x64_noname_f(&u8g2, rotation, u8x8_byte_arduino_hw_i2c, u8x8_gpio_and_delay_arduino);
  u8x8_SetPin_HW_I2C(getU8x8(), reset, clock, data);
}
};

// Initializes big 2,3" display from diymore.cc
class U8G2_EXT_SSD1309_128X64_NONAME_F_HW_I2C : public U8G2_EXT {
public: U8G2_EXT_SSD1309_128X64_NONAME_F_HW_I2C(const u8g2_cb_t *rotation, uint8_t reset = DISPLAY_RESET_PIN, uint8_t clock = SCL, uint8_t data = SDA) : U8G2_EXT() { 
  u8g2_Setup_ssd1309_i2c_128x64_noname0_f(&u8g2, rotation, u8x8_byte_arduino_hw_i2c, u8x8_gpio_and_delay_arduino); 
  u8x8_SetPin_HW_I2C(getU8x8(), reset, clock, data);
}
};

class U8G2_EXT_SSD1309_128X64_NONAME_F_4W_SW_SPI : public U8G2_EXT {
  public: U8G2_EXT_SSD1309_128X64_NONAME_F_4W_SW_SPI(const u8g2_cb_t *rotation, uint8_t clock = DISPLAY_SCK_PIN, uint8_t data = DISPLAY_MOSI_PIN, uint8_t cs = DISPLAY_SS_PIN, uint8_t dc = DISPLAY_DC_PIN, uint8_t reset = U8X8_PIN_NONE) : U8G2_EXT() {
    u8g2_Setup_ssd1309_128x64_noname0_f(&u8g2, rotation, u8x8_byte_arduino_4wire_sw_spi, u8x8_gpio_and_delay_arduino);
    u8x8_SetPin_4Wire_SW_SPI(getU8x8(), clock, data, cs, dc, reset);
  }
};

class U8G2_EXT_SSD1309_128X64_NONAME_F_4W_HW_SPI : public U8G2_EXT {
  public: U8G2_EXT_SSD1309_128X64_NONAME_F_4W_HW_SPI(const u8g2_cb_t *rotation, uint8_t cs = DISPLAY_SS_PIN, uint8_t dc = DISPLAY_DC_PIN, uint8_t reset = U8X8_PIN_NONE) : U8G2_EXT() {
    u8g2_Setup_ssd1309_128x64_noname0_f(&u8g2, rotation, u8x8_byte_arduino_hw_spi, u8x8_gpio_and_delay_arduino);
    u8x8_SetPin_4Wire_HW_SPI(getU8x8(), cs, dc, reset);
  }
};
