#pragma once

#ifndef _I2C_H_
#define _I2C_H_
#include <stdbool.h>
#include <stdint.h>

bool InitI2C(void);
void CloseI2C(void);

void SetI2CAddr(uint8_t value);

bool WriteReg(uint8_t reg, uint8_t value);
uint8_t ReadReg(uint8_t reg);
bool ReadBytesFromAddr(uint8_t reg, uint8_t* dest, uint8_t len);
bool WriteBytesToAddr(uint8_t reg, uint8_t* values, uint8_t len);

#endif
