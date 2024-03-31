#pragma once

#include "esphome.h"
#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include <Wire.h>
#include "Adafruit_VL6180X.h"

namespace esphome {
namespace vl6180x {

#define TAG_VL6180X "vl6180x"

enum VL6180X_GAIN { GAIN_1 = VL6180X_ALS_GAIN_1, GAIN_1_25 = VL6180X_ALS_GAIN_1_25, 
    GAIN_1_67 = VL6180X_ALS_GAIN_1_67, GAIN_2_5 = VL6180X_ALS_GAIN_2_5, GAIN_5 = VL6180X_ALS_GAIN_5, 
    GAIN_10 = VL6180X_ALS_GAIN_10, GAIN_20 = VL6180X_ALS_GAIN_20, GAIN_40 = VL6180X_ALS_GAIN_40 };

class VL6180XSensor : public PollingComponent {
public:
  VL6180XSensor();

  void setup() override;
  void update() override;
  void dump_config() override;
  void set_gain(uint8_t gain);

  void set_luminance_sensor(sensor::Sensor *lum_sensor) { this->luminance_sensor_ = lum_sensor; }
  void set_distance_sensor(sensor::Sensor *dist_sensor) { this->distance_sensor_ = dist_sensor; }
private:
  Adafruit_VL6180X vl;
  sensor::Sensor *luminance_sensor_{nullptr};
  sensor::Sensor *distance_sensor_{nullptr};
  uint8_t gain_;
};

} // namespace vl6180x
} // namespace esphome
