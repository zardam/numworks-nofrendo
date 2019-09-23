ifeq ($(PLATFORM),device)
SFLAGS += -DDEVICE
endif

ifeq ($(MODEL),n0110)
SFLAGS += -DN110
endif

include apps/nes/nofrendo/Makefile

apps += NES::App
app_headers += apps/nes/app.h

app_src += $(addprefix apps/nes/,\
  app.cpp \
  nes_controller.cpp \
  nes_view.cpp \
)

app_images += apps/nes/nes_icon.png

i18n_files += $(addprefix apps/nes/,\
  base.de.i18n\
  base.en.i18n\
  base.es.i18n\
  base.fr.i18n\
  base.pt.i18n\
)

$(eval $(call depends_on_image,apps/nes/app.cpp,apps/nes/nes_icon.png))
