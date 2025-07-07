import esphome.codegen as cg
from esphome.components import binary_sensor, uart
import esphome.config_validation as cv
from esphome.const import CONF_ID

DEPENDENCIES = ["uart"]
AUTO_LOAD = ["binary_sensor"]

blauberg_ns = cg.esphome_ns.namespace("blauberg_s14")
BlaubergS14Controller = blauberg_ns.class_(
    "BlaubergS14Controller", cg.Component, uart.UARTDevice
)

CONFIG_SCHEMA = (
    cv.Schema({cv.GenerateID(): cv.declare_id(BlaubergS14Controller)})
    .extend(cv.COMPONENT_SCHEMA)
    .extend(uart.UART_DEVICE_SCHEMA)
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)
