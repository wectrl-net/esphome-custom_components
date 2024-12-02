import esphome.codegen as cg
from esphome.components import modbus_controller
from esphome import config_validation as cv
from esphome.const import CONF_ID  # Import CONF_ID here

gree_versati_ns = cg.esphome_ns.namespace("gree_versati")
GreeVersati = gree_versati_ns.class_("GreeVersati", cg.Component)

CONF_CONTROLLER = "controller"

CONFIG_SCHEMA = cv.ensure_list(
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(GreeVersati),
            cv.Required(CONF_CONTROLLER): cv.use_id(modbus_controller.ModbusController),
        }
    )
)

async def to_code(config):
    for conf in config:
        var = cg.new_Pvariable(conf[CONF_ID])
        controller = await cg.get_variable(conf[CONF_CONTROLLER])
        cg.add(var.set_modbus_controller(controller))
        await cg.register_component(var, conf)
