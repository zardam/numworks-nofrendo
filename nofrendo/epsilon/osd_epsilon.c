#include <math.h>
#include <string.h>
#include <noftypes.h>
#include <bitmap.h>
#include <nofconfig.h>
#include <event.h>
#include <gui.h>
#include <log.h>
#include <nes.h>
#include <nes_pal.h>
#include <nesinput.h>
#include <osd.h>
#include <stdint.h>
#include "nofrendo_wrapper.h"

#define  DEFAULT_SAMPLERATE   22100
#define  DEFAULT_FRAGSIZE     128

#define  DEFAULT_WIDTH        256
#define  DEFAULT_HEIGHT       NES_VISIBLE_HEIGHT

char configfilename[]="na";

/* This is os-specific part of main() */
int osd_main(int argc, char *argv[])
{
   config.filename = configfilename;

   return main_loop("rom", system_autodetect);
}

/* File system interface */
void osd_fullname(char *fullname, const char *shortname)
{
   strncpy(fullname, shortname, PATH_MAX);
}

/* This gives filenames for storage of saves */
char *osd_newextension(char *string, char *ext)
{
   return string;
}

/* This gives filenames for storage of PCX snapshots */
int osd_makesnapname(char *filename, int len)
{
  return -1;
}

/*
** Audio
*/
static void (*audio_callback)(void *buffer, int length) = NULL;

void osd_setsound(void (*playfunc)(void *buffer, int length))
{
   //Indicates we should call playfunc() to get more data.
   audio_callback = playfunc;
}

static void osd_stopsound(void)
{
   audio_callback = NULL;
}


static int osd_init_sound(void)
{
	audio_callback = NULL;

	return 0;
}

void osd_getsoundinfo(sndinfo_t *info)
{
   info->sample_rate = DEFAULT_SAMPLERATE;
   info->bps = 16;
}

void osd_getvideoinfo(vidinfo_t *info)
{
   info->default_width = DEFAULT_WIDTH;
   info->default_height = DEFAULT_HEIGHT;
}

/* flip between full screen and windowed */
void osd_togglefullscreen(int code)
{
}

void osd_getinput(void)
{
  const int events[9]={
    event_joypad1_left,
    event_joypad1_up,
    event_joypad1_down,
    event_joypad1_right,
    event_joypad1_b,
    event_joypad1_a,
    event_joypad1_select,
    event_joypad1_start,
    event_joypad1_start,
  };
  static uint64_t old_keys_pressed = 0xffffffffffffffff;

  uint64_t cur_keys_pressed = readKeyboard();
  uint64_t chg_keys_pressed = cur_keys_pressed ^ old_keys_pressed;
  old_keys_pressed = cur_keys_pressed;

  if(cur_keys_pressed & (1<<17)) {
    event_get(event_hard_reset)(INP_STATE_MAKE);
  } else if(cur_keys_pressed > 511) {
    event_get(event_quit)(INP_STATE_MAKE);
  }
  for (int i=0; i<9; i++) {
    if (chg_keys_pressed & 1) {
      event_t evt = event_get(events[i]);
      if (evt) evt((cur_keys_pressed & 1) ? INP_STATE_MAKE : INP_STATE_BREAK);
    }
    chg_keys_pressed >>= 1;
    cur_keys_pressed >>= 1;
  }
}

static void osd_freeinput(void)
{
}

void osd_getmouse(int *x, int *y, int *button)
{
}

/*
** Shutdown
*/

/* this is at the bottom, to eliminate warnings */
void osd_shutdown()
{
	osd_stopsound();
	osd_freeinput();
}

/*
** Startup
*/

int osd_init()
{
	if (osd_init_sound())
		return -1;

	return 0;
}

#if DEVICE
extern const unsigned char _data_section_start_flash;
extern const unsigned char _data_section_start_ram;
extern const unsigned char _data_section_end_ram;

const char *osd_getromdata() {
#if N110
  return (char*) 0x90400000;
#else
  return (char*) (&_data_section_end_ram - &_data_section_start_ram + &_data_section_start_flash);
#endif
}
#else
extern const unsigned char _rom_data[];
const char *osd_getromdata() {
  return (char*) _rom_data;
}
#endif
