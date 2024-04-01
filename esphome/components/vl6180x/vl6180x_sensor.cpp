#include "vl6180x_sensor.h"

namespace esphome {
namespace vl6180x {

VL6180XSensor::VL6180XSensor() : PollingComponent(15000) {}

void VL6180XSensor::setup() {
    ESP_LOGCONFIG(TAG_VL6180X, "Setting up VL6180XSensor...");
    if (vl.begin()) {
        ESP_LOGCONFIG(TAG_VL6180X, "VL6180XSensor setup complete.");
    } else {
        ESP_LOGE(TAG_VL6180X, "Could not communicate with VL6180X sensor.");
    }
    ESP_LOGCONFIG("  ", "Luminance", this->luminance_sensor_);
    ESP_LOGCONFIG("  ", "Distance", this->distance_sensor_);
    this->gain_ = VL6180X_ALS_GAIN_1;
}

void VL6180XSensor::update() {
    float luminance = vl.readLux(this->gain_);
    ESP_LOGD(TAG_VL6180X, "Luminance measured: %f", luminance);
    if (this->luminance_sensor_ != nullptr)
    {
        this->luminance_sensor_->publish_state(luminance);
    }

    uint8_t range = vl.readRange();
    ESP_LOGCONFIG("measured range: %i", range);
    uint8_t status = vl.readRangeStatus();

    ESP_LOGCONFIG("meaasured Status: %i", status);

    if (status == VL6180X_ERROR_NONE) {
        ESP_LOGD(TAG_VL6180X, "Range measured: %i", range);
        if (this->distance_sensor_ != nullptr)
        {
            this->distance_sensor_->publish_state(range);
        }
    }

    // Log any errors.
    if  ((status >= VL6180X_ERROR_SYSERR_1) && (status <= VL6180X_ERROR_SYSERR_5)) {
        ESP_LOGE(TAG_VL6180X, "System error");
    }
    else if (status == VL6180X_ERROR_ECEFAIL) {
        ESP_LOGW(TAG_VL6180X, "ECE failure");
        if (this->distance_sensor_ != nullptr)
        {
            this->distance_sensor_->publish_state(range);
        }
    }
    else if (status == VL6180X_ERROR_NOCONVERGE) {
        ESP_LOGW(TAG_VL6180X, "No convergence");
        if (this->distance_sensor_ != nullptr)
        {
            this->distance_sensor_->publish_state(range);
        }
    }
    else if (status == VL6180X_ERROR_RANGEIGNORE) {
        ESP_LOGW(TAG_VL6180X, "Ignoring range");
        if (this->distance_sensor_ != nullptr)
        {
            this->distance_sensor_->publish_state(range);
        }
    }
    else if (status == VL6180X_ERROR_SNR) {
        ESP_LOGW(TAG_VL6180X, "Signal/Noise error");
        if (this->distance_sensor_ != nullptr)
        {
            this->distance_sensor_->publish_state(range);
        }
    }
    else if (status == VL6180X_ERROR_RAWUFLOW) {
        ESP_LOGW(TAG_VL6180X, "Raw reading underflow");
        if (this->distance_sensor_ != nullptr)
        {
            this->distance_sensor_->publish_state(range);
        }
    }
    else if (status == VL6180X_ERROR_RAWOFLOW) {
        ESP_LOGW(TAG_VL6180X, "Raw reading overflow");
        if (this->distance_sensor_ != nullptr)
        {
            this->distance_sensor_->publish_state(range);
        }
    }
    else if (status == VL6180X_ERROR_RANGEUFLOW) {
        ESP_LOGW(TAG_VL6180X, "Range reading underflow");
        if (this->distance_sensor_ != nullptr)
        {
            this->distance_sensor_->publish_state(range);
        }
    }
    else if (status == VL6180X_ERROR_RANGEOFLOW) {
        ESP_LOGW(TAG_VL6180X, "Range reading overflow");
        if (this->distance_sensor_ != nullptr)
        {
            this->distance_sensor_->publish_state(range);
        }
    }
}

void VL6180XSensor::dump_config() {
  ESP_LOGCONFIG(TAG_VL6180X, "VL6180X Sensor:");
  ESP_LOGCONFIG(TAG_VL6180X, "  Polling interval: %d ms", this->get_update_interval());
  ESP_LOGCONFIG(TAG_VL6180X, "  Gain Setting for Luminance: VL6180X_ALS_GAIN_5");
}

void VL6180XSensor::set_gain(uint8_t gain) {
    this->gain_ = gain;
}

} // namespace vl6180x
} // namespace esphome
