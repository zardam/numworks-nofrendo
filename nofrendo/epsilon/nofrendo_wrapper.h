#ifndef NOFRENDO_WRAPPER_H
#define NOFRENDO_WRAPPER_H

#include <stdint.h>
#include "../bitmap.h"

#ifdef __cplusplus
#define EXTERNC extern "C"
class NofrendoWrapper {
public:
  NofrendoWrapper();
  void run();
};
#else
#define EXTERNC
#endif

EXTERNC uint64_t readKeyboard();
EXTERNC uint32_t micros();
EXTERNC void draw(bitmap_t *bitmap, uint16_t *palette);
EXTERNC void draw_scanline(uint8_t *bitmap, uint16_t *palette, int scanline);

#endif
