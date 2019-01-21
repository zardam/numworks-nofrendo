NES_ROM ?= apps/nes/nofrendo/epsilon/2048.nes
SFLAGS += -Iapps/nes/nofrendo -Iapps/nes/nofrendo/nes -Iapps/nes/nofrendo/sndhrdw -Iapps/nes/nofrendo/libsnss -Iapps/nes/nofrendo/cpu
nof_objs = $(addprefix apps/nes/nofrendo/,\
	bitmap.o\
	config.o\
	cpu/dis6502.o\
	cpu/nes6502.o\
	event.o\
	libsnss/libsnss.o\
	log.o\
	mappers/map000.o\
	mappers/map001.o\
	mappers/map002.o\
	mappers/map003.o\
	mappers/map004.o\
	mappers/map005.o\
	mappers/map007.o\
	mappers/map008.o\
	mappers/map009.o\
	mappers/map011.o\
	mappers/map015.o\
	mappers/map016.o\
	mappers/map018.o\
	mappers/map019.o\
	mappers/map024.o\
	mappers/map032.o\
	mappers/map033.o\
	mappers/map034.o\
	mappers/map040.o\
	mappers/map041.o\
	mappers/map042.o\
	mappers/map046.o\
	mappers/map050.o\
	mappers/map064.o\
	mappers/map065.o\
	mappers/map066.o\
	mappers/map070.o\
	mappers/map073.o\
	mappers/map075.o\
	mappers/map078.o\
	mappers/map079.o\
	mappers/map085.o\
	mappers/map087.o\
	mappers/map093.o\
	mappers/map094.o\
	mappers/map099.o\
	mappers/map160.o\
	mappers/map229.o\
	mappers/map231.o\
	mappers/mapvrc.o\
	memguard.o\
	nes/mmclist.o\
	nes/nes.o\
	nes/nesinput.o\
	nes/nes_mmc.o\
	nes/nes_pal.o\
	nes/nes_ppu.o\
	nes/nes_rom.o\
	nes/nesstate.o\
	sndhrdw/fds_snd.o\
	sndhrdw/mmc5_snd.o\
	sndhrdw/nes_apu.o\
	sndhrdw/vrcvisnd.o\
	nofrendo.o\
	epsilon/nofrendo_wrapper.o\
	epsilon/osd_epsilon.o\
	epsilon/stubs.o\
)

ifneq ($(PLATFORM),device)
nof_objs += $(addprefix apps/nes/nofrendo/,\
	epsilon/rom.o\
)
apps/nes/nofrendo/epsilon/rom.c: FORCE
	@echo "BIN     $@"
	$(Q) echo "const unsigned char _rom_data[] = {" > $@
	$(Q) cat "$(NES_ROM)" | xxd -i >> $@
	$(Q) echo "};" >> $@

FORCE:

products += apps/nes/nofrendo/epsilon/rom.c
endif

$(nof_objs): SFLAGS := $(subst -Os,-O2,$(SFLAGS))

objs += $(nof_objs)
