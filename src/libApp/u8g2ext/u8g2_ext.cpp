#include "u8g2_ext.h"
#include "u8g2_ext_catalog.h"
#include "u8g2_ext_input.h"
#include "u8g2_ext_selection.h"
#include "u8g2_ext_message.h"
#include "u8g2_ext_value.h"

bool U8G2_EXT::UserInterfaceCatalog(KeyPad *extPad, const char *title)
{
  return ext_UserInterfaceCatalog(U8G2_EXT::getU8g2(), extPad, title);
};

bool U8G2_EXT::UserInterfaceUserCatalog(KeyPad *extPad, const char *title)
{
  return ext_UserInterfaceUserCatalog(U8G2_EXT::getU8g2(), extPad, title);
};

uint8_t U8G2_EXT::UserInterfaceMessage(KeyPad *extPad, const char *title1, const char *title2, const char *title3, const char *buttons)
{
  return ext_UserInterfaceMessage(U8G2_EXT::getU8g2(), extPad, title1, title2, title3, buttons);
};
uint8_t U8G2_EXT::UserInterfaceSelectionList(KeyPad *extPad, const char *title, uint8_t start_pos, const char *sl, boolean wrap)
{
  return ext_UserInterfaceSelectionList(U8G2_EXT::getU8g2(), extPad, title, start_pos, sl, wrap);
};

uint8_t U8G2_EXT::UserInterfaceInputValueBoolean(KeyPad *extPad, const char *title, boolean *value)
{
  return ext_UserInterfaceInputValueBoolean(U8G2_EXT::getU8g2(), extPad, title, value);
};

uint8_t U8G2_EXT::UserInterfaceInputValueInteger(KeyPad *extPad, const char *title, const char *pre, uint8_t *value, uint8_t lo, uint8_t hi, uint8_t digits, const char *post)
{
  return ext_UserInterfaceInputValueInteger(U8G2_EXT::getU8g2(), extPad, title, pre, value, lo, hi, digits, post);
};

uint8_t U8G2_EXT::UserInterfaceInputValueFloat(KeyPad *extPad, const char *title, const char *pre, float *value, float lo, float hi, uint8_t len, uint8_t dec, const char *post)
{
  return ext_UserInterfaceInputValueFloat(U8G2_EXT::getU8g2(), extPad, title, pre, value, lo,  hi,  len,  dec, post);
}

uint8_t U8G2_EXT::UserInterfaceInputValueDMS(KeyPad *extPad, const char *title, long *value, long lo, long hi, uint8_t digits1, char* symb1, char* symb2, char* symb3, char* symb_plus, char* symb_minus, bool display_seconds)
{
  return ext_UserInterfaceInputValueDMS(U8G2_EXT::getU8g2(), extPad, title, value, lo, hi, digits1, symb1, symb2, symb3, symb_plus, symb_minus, display_seconds);
};

uint8_t U8G2_EXT::UserInterfaceInputValueDate(KeyPad *extPad, const char *title, uint8_t& year, uint8_t& month, uint8_t& day)
{
  return ext_UserInterfaceInputValueDate(U8G2_EXT::getU8g2(), extPad, title, year, month, day);
};

uint8_t U8G2_EXT::UserInterfaceInputValueRA(KeyPad *extPad, long *value)
{
  return ext_UserInterfaceInputValueRA(U8G2_EXT::getU8g2(), extPad, value);
};

uint8_t U8G2_EXT::UserInterfaceInputValueDec(KeyPad *extPad, long *value)
{
  return ext_UserInterfaceInputValueDec(U8G2_EXT::getU8g2(), extPad, value);
};

uint8_t U8G2_EXT::UserInterfaceInputValueTime(KeyPad *extPad, long *value, bool hrs24)
{
  return ext_UserInterfaceInputValueTime(U8G2_EXT::getU8g2(), extPad, value, hrs24);
};

uint8_t U8G2_EXT::UserInterfaceInputValueLatitude(KeyPad *extPad, long *value)
{
  return ext_UserInterfaceInputValueLatitude(U8G2_EXT::getU8g2(), extPad, value);
};

uint8_t U8G2_EXT::UserInterfaceInputValueLongitude(KeyPad *extPad, long *value)
{
  return ext_UserInterfaceInputValueLongitude(U8G2_EXT::getU8g2(), extPad, value);
};

uint8_t U8G2_EXT::DrawFwNumeric(uint8_t x, uint8_t y, const char* text)
{
  return ext_DrawFwNumeric(U8G2_EXT::getU8g2(), x, y, text);
};

uint8_t U8G2_EXT::GetFwNumericWidth(const char* text)
{
  return ext_GetFwNumericWidth(U8G2_EXT::getU8g2(), text);
};
