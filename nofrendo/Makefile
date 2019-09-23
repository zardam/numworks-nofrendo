NES_ROM ?= apps/nes/nofrendo/epsilon/2048.nes
SFLAGS += -Iapps/nes/nofrendo -Iapps/nes/nofrendo/nes -Iapps/nes/nofrendo/sndhrdw -Iapps/nes/nofrendo/libsnss -Iapps/nes/nofrendo/cpu
nof_src = $(addprefix apps/nes/nofrendo/,\
	bitmap.c \
	config.c \
	cpu/dis6502.c \
	cpu/nes6502.c \
	event.c \
	libsnss/libsnss.c \
	log.c \
	mappers/map000.c \
	mappers/map001.c \
	mappers/map002.c \
	mappers/map003.c \
	mappers/map004.c \
	mappers/map005.c \
	mappers/map007.c \
	mappers/map008.c \
	mappers/map009.c \
	mappers/map011.c \
	mappers/map015.c \
	mappers/map016.c \
	mappers/map018.c \
	mappers/map019.c \
	mappers/map024.c \
	mappers/map032.c \
	mappers/map033.c \
	mappers/map034.c \
	mappers/map040.c \
	mappers/map041.c \
	mappers/map042.c \
	mappers/map046.c \
	mappers/map050.c \
	mappers/map064.c \
	mappers/map065.c \
	mappers/map066.c \
	mappers/map070.c \
	mappers/map073.c \
	mappers/map075.c \
	mappers/map078.c \
	mappers/map079.c \
	mappers/map085.c \
	mappers/map087.c \
	mappers/map093.c \
	mappers/map094.c \
	mappers/map099.c \
	mappers/map160.c \
	mappers/map229.c \
	mappers/map231.c \
	mappers/mapvrc.c \
	memguard.c \
	nes/mmclist.c \
	nes/nes.c \
	nes/nesinput.c \
	nes/nes_mmc.c \
	nes/nes_pal.c \
	nes/nes_ppu.c \
	nes/nes_rom.c \
	nes/nesstate.c \
	sndhrdw/fds_snd.c \
	sndhrdw/mmc5_snd.c \
	sndhrdw/nes_apu.c \
	sndhrdw/vrcvisnd.c \
	nofrendo.c \
	epsilon/nofrendo_wrapper.cpp \
	epsilon/osd_epsilon.c \
	epsilon/stubs.c \
)

ifneq ($(PLATFORM),device)
nof_src += $(addprefix apps/nes/nofrendo/,\
	epsilon/rom.c \
)
apps/nes/nofrendo/epsilon/rom.c: FORCE
	@echo "BIN     $@"
	$(Q) echo "const unsigned char _rom_data[] = {" > $@
	$(Q) cat "$(NES_ROM)" | xxd -i >> $@
	$(Q) echo "};" >> $@

FORCE:

products += apps/nes/nofrendo/epsilon/rom.c
endif

#$(call object_for,$(nof_src)): SFLAGS := $(subst -Os,-O2,$(SFLAGS))

app_src += $(nof_src)
