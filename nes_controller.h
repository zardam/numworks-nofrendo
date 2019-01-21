#ifndef NES_CONTROLLER_H
#define NES_CONTROLLER_H

#include <escher.h>
#include "nes_view.h"

class AppsContainer;

namespace NES {

class NesController : public ViewController {
  public:
    NesController();
    View * view() override;
  private:
    NesView m_view;
};

}

#endif
