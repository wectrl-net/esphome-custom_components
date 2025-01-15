"""Privacy Switch component for ESPHome."""
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import switch, uart
from esphome.const import CONF_ID, CONF_UART_ID

DEPENDENCIES = ['uart']
AUTO_LOAD = ['switch']

privacy_switch_ns = cg.esphome_ns.namespace('privacy_switch')
PrivacySwitch = privacy_switch_ns.class_('PrivacySwitch', switch.Switch, cg.Component)

CONFIG_SCHEMA = switch.SWITCH_SCHEMA.extend({
    cv.GenerateID(): cv.declare_id(PrivacySwitch),
    cv.Required(CONF_UART_ID): cv.use_id(uart.UARTComponent),
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await switch.register_switch(var, config)
    await cg.register_component(var, config)
    
    uart_component = await cg.get_variable(config[CONF_UART_ID])
    cg.add(var.set_uart_parent(uart_component)) 