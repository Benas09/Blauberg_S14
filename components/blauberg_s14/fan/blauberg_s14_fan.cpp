#include "blauberg_s14_fan.h"
#include "esphome/core/log.h"

namespace esphome {
namespace blauberg_s14 {

static const char *TAG = "BlaubergS14.fan";

void BlaubergS14Fan::set_controller(blauberg_s14::BlaubergS14Controller *controller) { this->controller_ = controller; }

fan::FanTraits BlaubergS14Fan::get_traits() { return fan::FanTraits(false, true, false, 3); }

void BlaubergS14Fan::control(const fan::FanCall &call) {
  ESP_LOGD(TAG, "Received BlaubergS14Fan::control");

  if (call.get_state().has_value()) {
    this->state = *call.get_state();
  }

  if (this->state && call.get_speed().has_value()) {
    auto speed = *call.get_speed();

    this->speed = speed;
  }

  if (!this->state) {
    this->controller_->setCurrentSpeed(0);
  } else {
    this->controller_->setCurrentSpeed(this->speed);
  }

  this->publish_state();
}

void BlaubergS14Fan::dump_config() { LOG_FAN("", "Empty fan", this); }
}  // namespace blauberg_s14
}  // namespace esphome