#pragma once

#include "esphome/core/component.h"
#include "esphome/components/blauberg_s14/blauberg_s14_controller.h"
#include "esphome/components/button/button.h"

namespace esphome {
namespace blauberg_s14 {

class BlaubergS14ResetFilterButton : public button::Button, public Component {
 public:
  BlaubergS14ResetFilterButton() = default;
  void setController(blauberg_s14::BlaubergS14Controller *controller) { this->controller_ = controller; }

 protected:
  void press_action() override;
  blauberg_s14::BlaubergS14Controller *controller_{nullptr};
};

}  // namespace blauberg_s14
}  // namespace esphome
