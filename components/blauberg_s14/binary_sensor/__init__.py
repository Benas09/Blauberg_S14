import logging

import esphome.codegen as cg
from esphome.components import binary_sensor
import esphome.config_validation as cv
from esphome.const import (
    CONF_ID,
    DEVICE_CLASS_OPENING,
    DEVICE_CLASS_PROBLEM,
    DEVICE_CLASS_RUNNING,
)

DEPENDENCIES = ["blauberg_s14"]

CONF_DAMPER_SENSOR = "damper_status"
CONF_DEFROSTING_SENSOR = "defrosting_status"
CONF_FILTER_REPLACEMENT_SENSOR = "filter_replacement_status"

blauberg_ns = cg.esphome_ns.namespace("blauberg_s14")

CONFIG_SCHEMA = cv.Schema(
    {
        cv.Required("blauberg_s14_id"): cv.use_id(blauberg_ns.BlaubergS14Controller),
        cv.Optional(CONF_DAMPER_SENSOR): binary_sensor.binary_sensor_schema(
            device_class=DEVICE_CLASS_OPENING, icon="mdi:hvac"
        ),
        cv.Optional(CONF_DEFROSTING_SENSOR): binary_sensor.binary_sensor_schema(
            device_class=DEVICE_CLASS_RUNNING, icon="mdi:snowflake-melt"
        ),
        cv.Optional(CONF_FILTER_REPLACEMENT_SENSOR): binary_sensor.binary_sensor_schema(
            device_class=DEVICE_CLASS_PROBLEM, icon="mdi:air-filter"
        ),
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    controller_ = await cg.get_variable(config["blauberg_s14_id"])

    if damper_status_sensor := config.get(CONF_DAMPER_SENSOR):
        sensor_var = await binary_sensor.new_binary_sensor(damper_status_sensor)
        cg.add(controller_.setDamperStatusSensor(sensor_var))

    if defrosting_status_sensor := config.get(CONF_DEFROSTING_SENSOR):
        sensor_var = await binary_sensor.new_binary_sensor(defrosting_status_sensor)
        cg.add(controller_.setDefrostingStatusSensor(sensor_var))

    if filter_replacement_status_sensor := config.get(CONF_FILTER_REPLACEMENT_SENSOR):
        sensor_var = await binary_sensor.new_binary_sensor(
            filter_replacement_status_sensor
        )
        cg.add(controller_.setFilterReplacementStatusSensor(sensor_var))
