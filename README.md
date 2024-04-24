# ESPHome VL6180X Component

This repository provides an ESPHome custom component for interfacing with the VL6180X Time-of-Flight (ToF) and ambient light sensor. The VL6180X sensor is capable of measuring distance up to a range of 200mm and ambient light, making it ideal for a variety of automation applications within ESPHome environments.

## Component Overview

The Adafruit VL6180X sensor is designed for easy integration with microcontroller platforms, including ESP32/ESP8266 using ESPHome. This custom component enables the sensor's functionalities directly within your ESPHome configuration.

### Adafruit_VL6180X.h and Adafruit_VL6180X.cpp

#### Overview
These files constitute the driver implementation for the Adafruit VL6180X ToF (Time-of-Flight) and ambient light sensor. They are essential for handling the low-level I2C communication, initializing the sensor, and facilitating data retrieval.

#### Key Features
- **I2C Communication**: Manages two-way communication between the ESPHome device and the VL6180X sensor using the I2C protocol.
- **Sensor Initialization**: Performs necessary setup tasks to prepare the sensor for operation, including setting default configuration settings.
- **Data Retrieval**: Provides functions to read distance and illuminance values from the sensor, handling necessary conversions and adjustments based on sensor settings.

### vl6180x_sensor.h

#### Overview
This header file defines the `VL6180XSensor` class for the ESPHome custom component, setting up the interface between ESPHome and the physical sensor.

##### Key Features
- **Class Definition**: Defines `VL6180XSensor` as a subclass of `PollingComponent`, allowing it to periodically update its state based on sensor readings.
- **Sensor Integration**: Incorporates two sensor fields within ESPHome: one for distance measurement and another for luminance measurement, each configured to periodically fetch data from the VL6180X sensor and update their state in Home Assistant.

### vl6180x_sensor.cpp

#### Overview
The implementation file for the ESPHome custom component that interacts with the VL6180X sensor. It includes comprehensive logic for configuring the sensor, retrieving measurements, and managing state updates within ESPHome.

#### Key Features
- **Sensor Setup**: Configures the sensor upon initialization, setting up various parameters like gain settings and measurement intervals.
- **Reading Values**: Implements methods to fetch distance and illuminance data from the sensor at the intervals specified in the ESPHome configuration.
- **State Publishing**: Handles the publishing of sensor data to Home Assistant, ensuring that the state is updated accurately and timely in response to changes in sensor readings.

### **sensor.py**:
This Python file is part of an ESPHome custom component setup, specifically designed to interface with the VL6180X sensor, a device capable of measuring both distance and illuminance. Below is a detailed breakdown of the file's contents and its functionalities.
- `esphome.codegen` and `esphome.config_validation`: Used for generating code and validating the configuration entries.
- `esphome.components.i2c` and `esphome.components.sensor`: Enable the component to use I2C communication and sensor functionalities within ESPHome.
- `esphome.const`: Provides constants used in defining sensor properties such as unit measurements and icons.
- **Namespace Declaration**: `vl6180x_ns` is a custom namespace created using `cg.esphome_ns.namespace("vl6180x")`, which helps in preventing naming conflicts across different components.
- **Component Class Definition**: `VL6180XComponent` is defined as a class within the `vl6180x_ns` namespace, inheriting from `cg.PollingComponent`, which facilitates periodic polling of the sensor data.
- `CONF_GAIN`: A string constant representing the gain setting in the sensor configuration.
- `VL6180X_GAIN`: An enumerated type representing different possible gain settings for the sensor

#### `to_code` Function
- **Purpose**: This asynchronous function takes the configuration dictionary and applies it to generate the necessary code to set up and register the sensor component within ESPHome.
- **Implementation**:
  - It initializes a new variable for the component instance.
  - Registers the component with its configuration.
  - Sets the gain of the sensor.
  - Dynamically adds illuminance and distance sensors if they are configured, using the mappings defined in `TYPES`.

This file serves as a foundational element for integrating the VL6180X sensor into ESPHome, offering flexibility and ease of use through its well-defined configuration schema and dynamic setup capabilities.

## Features

- **Distance Measurement**: Measures the distance to objects up to 200mm away and provides this information in millimeters.
- **Ambient Light Measurement**: Measures ambient light levels and provides this information in lux.
- **Custom Gains for Light Measurement**: Supports various gain settings to adjust the sensitivity of the light sensor.

## Configuration

To integrate the VL6180X sensor into your ESPHome setup, follow these steps:

1. **Include the Custom Component**:
   - Ensure that this repository is included in your ESPHome configuration by using the github link.

2. **Modify Your ESPHome Device Configuration**:
   - Add the sensor configuration to your device's YAML file. An example configuration is provided below:

```yaml
sensor:
  - platform: vl6180x
    update_interval: 30s
    distance:
      name: "VL6180X Distance"
    illuminance:
      name: "VL6180X Luminance"