import esphome.codegen as cg
from esphome.components import fan, output
import esphome.config_validation as cv
from esphome.const import CONF_OUTPUT_ID

DEPENDENCIES = ["blauberg_s14"]

blauberg_ns = cg.esphome_ns.namespace("blauberg_s14")
BlaubergS14Fan = blauberg_ns.class_("BlaubergS14Fan", cg.Component, fan.Fan)

CONFIG_SCHEMA = fan.FAN_SCHEMA.extend(
    {
        cv.GenerateID(CONF_OUTPUT_ID): cv.declare_id(BlaubergS14Fan),
        cv.Required("blauberg_s14_id"): cv.use_id(blauberg_ns.BlaubergS14Controller),
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_OUTPUT_ID])
    await cg.register_component(var, config)
    await fan.register_fan(var, config)

    controller_ = await cg.get_variable(config["blauberg_s14_id"])
    cg.add(var.set_controller(controller_))
