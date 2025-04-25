#include "blauberg_s14_controller.h"
#include "esphome/core/log.h"

namespace esphome {
namespace blauberg_s14 {
static const char *TAG = "BlaubergS14.controller";

void BlaubergS14Controller::setCurrentSpeed(int currentSpeed) {
  switch (currentSpeed) {
    case 0:
      this->currentSpeed = BlaubergS14Controller::S14_SPEED_0;
      break;
    case 1:
      this->currentSpeed = BlaubergS14Controller::S14_SPEED_1;
      break;
    case 2:
      this->currentSpeed = BlaubergS14Controller::S14_SPEED_2;
      break;
    case 3:
      this->currentSpeed = BlaubergS14Controller::S14_SPEED_3;
      break;
    default:
      this->currentSpeed = BlaubergS14Controller::S14_SPEED_0;
  }

  ESP_LOGD(TAG, "BlaubergS14Controller::setCurrentSpeed %d", this->currentSpeed);
}

void BlaubergS14Controller::setCurrentDamper(bool currentDamper) {
  this->currentDamper = currentDamper ? BlaubergS14Controller::S14_DAMPER_ON : BlaubergS14Controller::S14_DAMPER_OFF;

  if (this->sensor_damper_ != nullptr) {
    this->sensor_damper_->publish_state(this->currentDamper == BlaubergS14Controller::S14_DAMPER_ON);
  }

  ESP_LOGD(TAG, "BlaubergS14Controller::setCurrentDamper %d", (int) currentDamper);
}

void BlaubergS14Controller::setResetFilter(bool resetFilter) {
  this->currentResetFilter =
      resetFilter ? BlaubergS14Controller::S14_RESET_FILTER_ON : BlaubergS14Controller::S14_RESET_FILTER_OFF;

  ESP_LOGD(TAG, "BlaubergS14Controller::setResetFilter %d", (int) resetFilter);
}

void BlaubergS14Controller::setup() {
  if (this->sensor_damper_ != nullptr) {
    this->sensor_damper_->publish_state(this->currentDamper == BlaubergS14Controller::S14_DAMPER_ON);
  }

  if (this->sensor_isDefrosting_ != nullptr) {
    this->sensor_isDefrosting_->publish_state(this->isDefrosting);
  }

  if (this->sensor_filterReplacementRequired_ != nullptr) {
    this->sensor_filterReplacementRequired_->publish_state(this->filterReplacementRequired);
  }
}

void BlaubergS14Controller::loop() {
  if (0 == this->lastMillis || this->lastMillis + 90 < millis()) {
    if (0 == this->defrostingFromMillis || millis() - this->defrostingFromMillis > DEFROSTING_TIME) {
      write(this->currentSpeed | this->currentDamper | this->currentResetFilter);

      if (this->isDefrosting) {
        this->isDefrosting = false;

        if (this->sensor_isDefrosting_ != nullptr) {
          this->sensor_isDefrosting_->publish_state(this->isDefrosting);
        }
      }
    } else {
      write(S14_SPEED_0 | this->currentDamper | this->currentResetFilter);

      if (!this->isDefrosting) {
        this->isDefrosting = true;

        if (this->sensor_isDefrosting_ != nullptr) {
          this->sensor_isDefrosting_->publish_state(this->isDefrosting);
        }
      }
    }

    this->lastMillis = millis();
  }

  bool responseReceived = false;
  int response = 0x00;

  while (available()) {
    response = read();
    responseReceived = true;
  }

  if (responseReceived) {
    if (this->lastResponse != response) {
      if (S14_RESPONSE_DEFROSTING_REQUIRED == response) {
        this->defrostingFromMillis = millis();
      }

      if ((S14_RESPONSE_FILTER_REPLACEMENT_REQUIRED == response) != this->filterReplacementRequired) {
        this->filterReplacementRequired = S14_RESPONSE_FILTER_REPLACEMENT_REQUIRED == response;

        if (!this->filterReplacementRequired) {
          this->setResetFilter(false);
        }

        if (this->sensor_filterReplacementRequired_ != nullptr) {
          this->sensor_filterReplacementRequired_->publish_state(this->filterReplacementRequired);
        }
      }
    }

    this->lastResponse = response;
    this->lastMillis = millis();
  }
}

}  // namespace blauberg_s14
}  // namespace esphome