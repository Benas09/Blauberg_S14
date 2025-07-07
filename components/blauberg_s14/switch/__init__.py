import esphome.codegen as cg
from esphome.components import output, switch
import esphome.config_validation as cv
from esphome.const import CONF_OUTPUT

DEPENDENCIES = ["blauberg_s14"]

blauberg_ns = cg.esphome_ns.namespace("blauberg_s14")
BlaubergS14Switch = blauberg_ns.class_("BlaubergS14Switch", switch.Switch, cg.Component)

CONFIG_SCHEMA = (
    switch.switch_schema(BlaubergS14Switch)
    .extend(
        {
            cv.Required("blauberg_s14_id"): cv.use_id(
                blauberg_ns.BlaubergS14Controller
            ),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
)


async def to_code(config):
    var = await switch.new_switch(config)
    await cg.register_component(var, config)

    controller_ = await cg.get_variable(config["blauberg_s14_id"])
    cg.add(var.setController(controller_))
