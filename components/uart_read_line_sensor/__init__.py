"""UART Read Line Sensor component for ESPHome."""
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import text_sensor, uart
from esphome.const import CONF_ID, CONF_UART_ID

DEPENDENCIES = ['uart']
AUTO_LOAD = ['text_sensor']

CONF_SWITCH_ID = 'switch_id'

uart_read_line_sensor_ns = cg.esphome_ns.namespace('uart_read_line_sensor')
UartReadLineSensor = uart_read_line_sensor_ns.class_(
    'UartReadLineSensor', cg.Component, uart.UARTDevice, text_sensor.TextSensor
)

CONFIG_SCHEMA = text_sensor.text_sensor_schema().extend({
    cv.GenerateID(): cv.declare_id(UartReadLineSensor),
    cv.Required(CONF_UART_ID): cv.use_id(uart.UARTComponent),
    cv.Required(CONF_SWITCH_ID): cv.use_id(cg.Switch),
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await text_sensor.register_text_sensor(var, config)
    
    uart_component = await cg.get_variable(config[CONF_UART_ID])
    cg.add(var.set_uart_parent(uart_component))
    
    switch = await cg.get_variable(config[CONF_SWITCH_ID])
    cg.add(var.set_privacy_switch(switch)) 