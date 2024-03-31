import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c, sensor
from esphome.const import (
    STATE_CLASS_MEASUREMENT,
    CONF_ID,
    CONF_ILLUMINANCE,
    CONF_DISTANCE,
    UNIT_LUX,
    ICON_LIGHTBULB,
    ICON_RULER,
    DEVICE_CLASS_ILLUMINANCE,
)
from esphome import pins

vl6180x_ns = cg.esphome_ns.namespace("vl6180x")
VL6180XComponent = vl6180x_ns.class_(
    "VL6180XSensor", cg.PollingComponent
)

# Adjust or remove configuration parameters that are not relevant to VL6180X
CONF_GAIN = "gain"
VL6180X_GAIN = vl6180x_ns.enum("VL6180X_GAIN")

# For the VL6180X, gain settings might be more relevant than signal rate limit or long range mode
GAIN_OPTIONS = {
    "1.0": VL6180X_GAIN.GAIN_1,
    "1.25": VL6180X_GAIN.GAIN_1_25,
    "1.67": VL6180X_GAIN.GAIN_1_67,
    "2.5": VL6180X_GAIN.GAIN_2_5,
    "5.0": VL6180X_GAIN.GAIN_5,
    "10.0": VL6180X_GAIN.GAIN_10,
    "20.0": VL6180X_GAIN.GAIN_20,
    "40.0": VL6180X_GAIN.GAIN_40,
}

def check_timeout(value):
    value = cv.positive_time_period_microseconds(value)
    if value.total_seconds > 60:
        raise cv.Invalid("Maximum timeout cannot be greater than 60 seconds")
    return value

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(VL6180XComponent),
            cv.Optional(CONF_ILLUMINANCE): sensor.sensor_schema(
                unit_of_measurement=UNIT_LUX,
                icon=ICON_LIGHTBULB,
                accuracy_decimals=2,
                device_class=DEVICE_CLASS_ILLUMINANCE,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_DISTANCE): sensor.sensor_schema(
                unit_of_measurement="mm",
                icon=ICON_RULER,
                accuracy_decimals=2,
                device_class="distance",
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_GAIN, default="1.0"): cv.enum(GAIN_OPTIONS),
        }
    )
    .extend(cv.polling_component_schema("60s"))
)

TYPES = {
    CONF_ILLUMINANCE: "set_luminance_sensor",
    CONF_DISTANCE: "set_distance_sensor",
}


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    cg.add(var.set_gain(config[CONF_GAIN]))

    for key, funcName in TYPES.items():
        if key in config:
            sens = await sensor.new_sensor(config[key])
            cg.add(getattr(var, funcName)(sens))