#pragma once

#include "esphome/core/component.h"
#include "esphome/components/switch/switch.h"
#include "esphome/components/blauberg_s14/blauberg_s14_controller.h"

namespace esphome {
namespace blauberg_s14 {

class BlaubergS14Switch : public switch_::Switch, public Component {
 public:
  void setController(blauberg_s14::BlaubergS14Controller *controller) { this->controller_ = controller; }

  void setup() override;
  float get_setup_priority() const override { return setup_priority::HARDWARE - 1.0f; }
  void dump_config() override;

 protected:
  void write_state(bool state) override;

  blauberg_s14::BlaubergS14Controller *controller_{nullptr};
};

}  // namespace blauberg_s14
}  // namespace esphome
