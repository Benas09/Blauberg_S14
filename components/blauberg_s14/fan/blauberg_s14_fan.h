#pragma once

#include "esphome/components/fan/fan.h"
#include "esphome/core/component.h"
#include "esphome/components/blauberg_s14/blauberg_s14_controller.h"

namespace esphome {
namespace blauberg_s14 {

class BlaubergS14Fan : public Component, public fan::Fan {
 public:
  void set_controller(blauberg_s14::BlaubergS14Controller *controller);

  void dump_config() override;
  // void set_output(output::BinaryOutput *output) { this->output_ = output; }
  // void set_oscillating(output::BinaryOutput *oscillating) { this->oscillating_ = oscillating; }
  // void set_direction(output::BinaryOutput *direction) { this->direction_ = direction; }
  fan::FanTraits get_traits() override;

 protected:
  blauberg_s14::BlaubergS14Controller *controller_{nullptr};

  void control(const fan::FanCall &call) override;
  void write_state_();
};

}  // namespace blauberg_s14
}  // namespace esphome