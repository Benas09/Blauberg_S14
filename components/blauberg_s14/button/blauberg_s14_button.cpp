#include "blauberg_s14_button.h"
#include "esphome/core/log.h"

namespace esphome {
namespace blauberg_s14 {

static const char *const TAG = "BlaubergS14Button.button";

void BlaubergS14ResetFilterButton::press_action() {
  ESP_LOGI(TAG, "Resetting BlaubergS14 filter");

  this->controller_->setResetFilter(true);
}

}  // namespace blauberg_s14
}  // namespace esphome
