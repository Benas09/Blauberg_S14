#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/binary_sensor/binary_sensor.h"

namespace esphome {
namespace blauberg_s14 {

class BlaubergS14Controller : public Component, public uart::UARTDevice {
  static const int S14_SPEED_0 = 0x00;
  static const int S14_SPEED_1 = 0x01;
  static const int S14_SPEED_2 = 0x02;
  static const int S14_SPEED_3 = 0x03;

  static const int S14_DAMPER_OFF = 0x00;
  static const int S14_DAMPER_ON = 0x08;

  static const int S14_RESET_FILTER_OFF = 0x00;
  static const int S14_RESET_FILTER_ON = 0x04;

  static const int S14_RESPONSE_OK = 0x00;
  static const int S14_RESPONSE_FILTER_REPLACEMENT_REQUIRED = 0x01;
  static const int S14_RESPONSE_DEFROSTING_REQUIRED = 0x02;

  static const int DEFROSTING_TIME = 120000;

 public:
  void setDamperStatusSensor(binary_sensor::BinarySensor *damperStatusSensor) {
    this->sensor_damper_ = damperStatusSensor;
  }
  void setDefrostingStatusSensor(binary_sensor::BinarySensor *defrostingStatusSensor) {
    this->sensor_isDefrosting_ = defrostingStatusSensor;
  }
  void setFilterReplacementStatusSensor(binary_sensor::BinarySensor *filterReplacementStatusSensor) {
    this->sensor_filterReplacementRequired_ = filterReplacementStatusSensor;
  }

  void setCurrentSpeed(int currentSpeed);
  void setCurrentDamper(bool currentDamper);
  void setResetFilter(bool currentDamper);

  void setup() override;
  void loop() override;
  // float get_setup_priority() const override;
  // void dump_config() override;

 protected:
  binary_sensor::BinarySensor *sensor_damper_{nullptr};
  binary_sensor::BinarySensor *sensor_isDefrosting_{nullptr};
  binary_sensor::BinarySensor *sensor_filterReplacementRequired_{nullptr};

 private:
  long lastMillis = 0;
  long defrostingFromMillis = 0;
  bool isDefrosting = false;
  bool filterReplacementRequired = false;
  int currentSpeed = S14_SPEED_0;
  int currentDamper = S14_DAMPER_OFF;
  int currentResetFilter = S14_RESET_FILTER_OFF;
  int lastResponse = S14_RESPONSE_OK;
};

}  // namespace blauberg_s14
}  // namespace esphome