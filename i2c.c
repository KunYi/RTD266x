#include <stdbool.h>
#include <stdint.h>

bool InitI2C(void)
{
  // TODO: need implement
  return true;
}

void CloseI2C(void)
{
  // TODO: need implement
  ;
}

void SetI2CAddr(uint8_t value)
{
  // TODO: need implement
  (void) value;
}

bool WriteReg(uint8_t reg, uint8_t value)
{
  // TODO: need implement
  (void) reg;
  (void) value;
  return true;
}

uint8_t ReadReg(uint8_t reg)
{
  // TODO: need implement
  (void) reg;
  return 0;
}

bool ReadBytesFromAddr(uint8_t reg, uint8_t* dest, uint8_t len)
{
  // TODO: need implement
  (void) reg;
  (void) dest;
  (void) len;
  return true;
}

bool WriteBytesToAddr(uint8_t reg, uint8_t* values, uint8_t len)
{
  // TODO: need implement
  (void) reg;
  (void) values;
  (void) len;
  return true;
}
