#include "app.h"
#include "../i18n.h"
#include "../apps_container.h"
#include "nes_icon.h"

extern "C" {
#include <assert.h>
#include <epsilon/nofrendo_wrapper.h>
}

namespace NES {

I18n::Message App::Descriptor::name() {
  return I18n::Message::NES;
}

I18n::Message App::Descriptor::upperName() {
  return I18n::Message::NESCapital;
}

const Image * App::Descriptor::icon() {
  return ImageStore::NesIcon;
}

App::Descriptor * App::Snapshot::descriptor() {
  static Descriptor descriptor;
  return &descriptor;
}

App * App::Snapshot::unpack(Container * container) {
  return new (container->currentAppBuffer()) App(container, this);
}

App::Snapshot::Snapshot(){
}

void App::didBecomeActive(Window * window) {
  ::App::didBecomeActive(window);

  NofrendoWrapper nofrendoWrapper;
  nofrendoWrapper.run();

  m_appsContainer->switchTo(m_appsContainer->appSnapshotAtIndex(0));
}

void App::willBecomeInactive() {
  ::App::willBecomeInactive();
}

App::App(Container * container, Snapshot * snapshot) :
  ::App(snapshot, &m_nesController),
  m_appsContainer((AppsContainer*) container)
{
}

}
