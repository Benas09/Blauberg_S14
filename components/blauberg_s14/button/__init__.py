import esphome.codegen as cg
from esphome.components import button
import esphome.config_validation as cv
from esphome.const import CONF_OUTPUT

DEPENDENCIES = ["blauberg_s14"]

blauberg_ns = cg.esphome_ns.namespace("blauberg_s14")
BlaubergS14ResetFilterButton = blauberg_ns.class_(
    "BlaubergS14ResetFilterButton", button.Button, cg.Component
)

CONFIG_SCHEMA = button.button_schema(BlaubergS14ResetFilterButton).extend(
    {
        cv.Required("blauberg_s14_id"): cv.use_id(blauberg_ns.BlaubergS14Controller),
    }
)


async def to_code(config):
    var = await button.new_button(config)
    await cg.register_component(var, config)

    controller_ = await cg.get_variable(config["blauberg_s14_id"])
    cg.add(var.setController(controller_))
