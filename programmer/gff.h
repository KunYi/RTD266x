#pragma once

#ifndef _GFF_H_
#define _GFF_H_
#include <stdbool.h>
#include <stdint.h>

uint32_t ComputeGffDecodedSize(uint8_t* data_ptr, uint32_t data_len);
bool DecodeGff(uint8_t* data_ptr, uint32_t data_len, uint8_t* dest);

#endif
