include apps/nes/nofrendo/Makefile

apps += NES::App
app_headers += apps/nes/app.h

app_objs += $(addprefix apps/nes/,\
  app.o\
  nes_controller.o\
  nes_view.o\
)

app_images += apps/nes/nes_icon.png

i18n_files += $(addprefix apps/nes/,\
  base.de.i18n\
  base.en.i18n\
  base.es.i18n\
  base.fr.i18n\
  base.pt.i18n\
)
