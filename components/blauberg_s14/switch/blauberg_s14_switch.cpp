#include "blauberg_s14_switch.h"
#include "esphome/core/log.h"

namespace esphome {
namespace blauberg_s14 {

static const char *const TAG = "output.switch";

void BlaubergS14Switch::dump_config() { LOG_SWITCH("", "BlaubergS14Switch Switch", this); }

void BlaubergS14Switch::setup() {
  ESP_LOGCONFIG(TAG, "Setting up BlaubergS14Switch Switch '%s'...", this->name_.c_str());

  bool initial_state = this->get_initial_state_with_restore_mode().value_or(false);

  if (initial_state) {
    this->turn_on();
  } else {
    this->turn_off();
  }
}

void BlaubergS14Switch::write_state(bool state) {
  this->controller_->setCurrentDamper(state);

  this->publish_state(state);
}
}  // namespace blauberg_s14
}  // namespace esphome
