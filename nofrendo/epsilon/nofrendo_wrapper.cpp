#include <ion.h>
#include <kandinsky.h>
#include "nofrendo_wrapper.h"
#ifdef EPSILON_DEVICE_BENCH
#include "../../ion/src/device/display.h"
#endif

extern "C" {
  #include <nes.h>
  #include <event.h>
  #include <osd.h>
  #include <gui.h>
  #include "../bitmap.h"
}

NofrendoWrapper::NofrendoWrapper()
{
}

void NofrendoWrapper::run() {
  Ion::Display::pushRectUniform(KDRect(0, 0, Ion::Display::Width, Ion::Display::Height), KDColorBlack);
  nofrendo_main(0, NULL);
}

void draw_scanline(uint8_t *bmp, uint16_t *palette, int scanline) {
  if(scanline < 0 || scanline >= Ion::Display::Height) {
    return;
  }
  int xoffset = (Ion::Display::Width - NES_SCREEN_WIDTH) / 2;
  int yoffset = (Ion::Display::Height - NES_SCREEN_HEIGHT) / 2;
#if EPSILON_DEVICE_BENCH
  Ion::Display::Device::setDrawingArea(KDRect(xoffset, scanline+yoffset, NES_SCREEN_WIDTH, 1), Ion::Display::Device::Orientation::Portrait);
  *Ion::Display::Device::CommandAddress  = Ion::Display::Device::Command::MemoryWrite;
  uint8_t *pixels = bmp + NES_SCREEN_WIDTH + 7;
  size_t numberOfPixels = NES_SCREEN_WIDTH;
  while (numberOfPixels >= 32) {
    *Ion::Display::Device::DataAddress = palette[*pixels--];
    *Ion::Display::Device::DataAddress = palette[*pixels--];
    *Ion::Display::Device::DataAddress = palette[*pixels--];
    *Ion::Display::Device::DataAddress = palette[*pixels--];
    *Ion::Display::Device::DataAddress = palette[*pixels--];
    *Ion::Display::Device::DataAddress = palette[*pixels--];
    *Ion::Display::Device::DataAddress = palette[*pixels--];
    *Ion::Display::Device::DataAddress = palette[*pixels--];
    *Ion::Display::Device::DataAddress = palette[*pixels--];
    *Ion::Display::Device::DataAddress = palette[*pixels--];
    *Ion::Display::Device::DataAddress = palette[*pixels--];
    *Ion::Display::Device::DataAddress = palette[*pixels--];
    *Ion::Display::Device::DataAddress = palette[*pixels--];
    *Ion::Display::Device::DataAddress = palette[*pixels--];
    *Ion::Display::Device::DataAddress = palette[*pixels--];
    *Ion::Display::Device::DataAddress = palette[*pixels--];
    *Ion::Display::Device::DataAddress = palette[*pixels--];
    *Ion::Display::Device::DataAddress = palette[*pixels--];
    *Ion::Display::Device::DataAddress = palette[*pixels--];
    *Ion::Display::Device::DataAddress = palette[*pixels--];
    *Ion::Display::Device::DataAddress = palette[*pixels--];
    *Ion::Display::Device::DataAddress = palette[*pixels--];
    *Ion::Display::Device::DataAddress = palette[*pixels--];
    *Ion::Display::Device::DataAddress = palette[*pixels--];
    *Ion::Display::Device::DataAddress = palette[*pixels--];
    *Ion::Display::Device::DataAddress = palette[*pixels--];
    *Ion::Display::Device::DataAddress = palette[*pixels--];
    *Ion::Display::Device::DataAddress = palette[*pixels--];
    *Ion::Display::Device::DataAddress = palette[*pixels--];
    *Ion::Display::Device::DataAddress = palette[*pixels--];
    *Ion::Display::Device::DataAddress = palette[*pixels--];
    *Ion::Display::Device::DataAddress = palette[*pixels--];
    numberOfPixels -= 32;
  }

#else
  for(int x=0; x<NES_SCREEN_WIDTH; x++) {
    Ion::Display::pushRectUniform(
      KDRect(x+xoffset, scanline+yoffset, 1, 1),
      KDColor::RGB16(palette[bmp[x+8]])
    );
  }
#endif
}

#if EPSILON_DEVICE_BENCH
uint32_t micros() {
  // Here, we can use the current value of the systick counter to get a
  // microsecond resolution counter. The problem is that the systick interrupt
  // may occur between reading millis_elapsed and reading the current value
  // of the systick counter. To cope with this, we do two consecutive reading
  // of both values. Do not forget that the counter counts backwards down to zero.
  uint32_t c1 = CM4.SYST_CVR()->getCURRENT();
  uint32_t ms1 = Ion::Timing::millis();
  uint32_t c2 = CM4.SYST_CVR()->getCURRENT();
  uint32_t ms2 = Ion::Timing::millis();
  uint32_t load = CM4.SYST_RVR()->getRELOAD();
  // If c1 > c2, then no systick interrupt occured between reading c1 and ms1, so ms1
  // value is correct, else an interrupt occured and ms2 value is correct. So we
  // have the milliseconds part : "((c1 > c2) ? ms1 : ms2) * 1000"
  // Then, we just add and scale the value of c2, as it is correct in both case.
  // We do "(load - c2)" to convert from a backward count to a forward count,
  // and then scale it to microseconds "* 1000) / (load + 1)" (as load is
  // the number of ticks per milliseconds minus one)
  return ((c1 > c2) ? ms1 : ms2) * 1000 + ((load - c2) * 1000) / (load + 1);
}
#else
#include <chrono>

static auto start = std::chrono::high_resolution_clock::now();

uint32_t micros() {
  Ion::Timing::msleep(0);
  auto elapsed = std::chrono::high_resolution_clock::now() - start;
  return std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
}
#endif

void draw(bitmap_t *bmp, uint16 *palette) {
  int xoffset = (Ion::Display::Width - bmp->width) / 2;
  int yoffset = (Ion::Display::Height - bmp->height) / 2;
#if EPSILON_DEVICE_BENCH
    for(int y=0; y<bmp->height; y++) {
      Ion::Display::Device::setDrawingArea(KDRect(xoffset, y+yoffset, bmp->width, 1), Ion::Display::Device::Orientation::Portrait);

      *Ion::Display::Device::CommandAddress  = Ion::Display::Device::Command::MemoryWrite;
      uint8_t *pixels = bmp->line[y] + bmp->width;
      size_t numberOfPixels = bmp->width;
      while (numberOfPixels >= 32) {
        *Ion::Display::Device::DataAddress = palette[*pixels--];
        *Ion::Display::Device::DataAddress = palette[*pixels--];
        *Ion::Display::Device::DataAddress = palette[*pixels--];
        *Ion::Display::Device::DataAddress = palette[*pixels--];
        *Ion::Display::Device::DataAddress = palette[*pixels--];
        *Ion::Display::Device::DataAddress = palette[*pixels--];
        *Ion::Display::Device::DataAddress = palette[*pixels--];
        *Ion::Display::Device::DataAddress = palette[*pixels--];
        *Ion::Display::Device::DataAddress = palette[*pixels--];
        *Ion::Display::Device::DataAddress = palette[*pixels--];
        *Ion::Display::Device::DataAddress = palette[*pixels--];
        *Ion::Display::Device::DataAddress = palette[*pixels--];
        *Ion::Display::Device::DataAddress = palette[*pixels--];
        *Ion::Display::Device::DataAddress = palette[*pixels--];
        *Ion::Display::Device::DataAddress = palette[*pixels--];
        *Ion::Display::Device::DataAddress = palette[*pixels--];
        *Ion::Display::Device::DataAddress = palette[*pixels--];
        *Ion::Display::Device::DataAddress = palette[*pixels--];
        *Ion::Display::Device::DataAddress = palette[*pixels--];
        *Ion::Display::Device::DataAddress = palette[*pixels--];
        *Ion::Display::Device::DataAddress = palette[*pixels--];
        *Ion::Display::Device::DataAddress = palette[*pixels--];
        *Ion::Display::Device::DataAddress = palette[*pixels--];
        *Ion::Display::Device::DataAddress = palette[*pixels--];
        *Ion::Display::Device::DataAddress = palette[*pixels--];
        *Ion::Display::Device::DataAddress = palette[*pixels--];
        *Ion::Display::Device::DataAddress = palette[*pixels--];
        *Ion::Display::Device::DataAddress = palette[*pixels--];
        *Ion::Display::Device::DataAddress = palette[*pixels--];
        *Ion::Display::Device::DataAddress = palette[*pixels--];
        *Ion::Display::Device::DataAddress = palette[*pixels--];
        *Ion::Display::Device::DataAddress = palette[*pixels--];
        numberOfPixels -= 32;
      }
      while (numberOfPixels--) {
        *Ion::Display::Device::DataAddress = palette[*pixels--];
      }
    }
#else
    for(int x=0; x<bmp->width; x++) {
      for(int y=0; y<bmp->height; y++) {
        Ion::Display::pushRectUniform(
          KDRect(x+xoffset, y+yoffset, 1, 1),
          KDColor::RGB16(palette[bmp->line[y][x]])
        );
      }
    }
#endif
}

uint64_t readKeyboard() {
  return Ion::Keyboard::scan();
}
