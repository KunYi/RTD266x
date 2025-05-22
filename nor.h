#pragma once

#ifndef _NOR_H_
#define _NOR_H_
#include <stdint.h>

struct FlashDesc {
  const char* device_name;
  uint32_t    jedec_id;
  uint32_t    size_kb;
  uint32_t    page_size;
  uint32_t    block_size_kb;
};


#endif
