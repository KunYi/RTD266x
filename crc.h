#pragma once

#ifndef _CRC_H_
#define _CRC_H_
#include <stdint.h>

void InitCRC();
void ProcessCRC(const uint8_t *data, int len);
uint8_t GetCRC();

#endif
