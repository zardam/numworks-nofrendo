#include "nes_controller.h"

namespace NES {

NesController::NesController() :
  ViewController(nullptr),
  m_view()
{
}

View * NesController::view() {
  return &m_view;
}

}
