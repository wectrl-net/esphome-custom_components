 """UART Read Line Sensor component for ESPHome."""
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import text_sensor, uart
from esphome.const import CONF_ID, CONF_SWITCH_ID

DEPENDENCIES = ['uart']
AUTO_LOAD = ['text_sensor']

uart_read_line_sensor_ns = cg.esphome_ns.namespace('uart_read_line_sensor')
UartReadLineSensor = uart_read_line_sensor_ns.class_(
    'UartReadLineSensor', cg.Component, uart.UARTDevice, text_sensor.TextSensor
)

CONFIG_SCHEMA = text_sensor.TEXT_SENSOR_SCHEMA.extend({
    cv.GenerateID(): cv.declare_id(UartReadLineSensor),
    cv.Required(CONF_SWITCH_ID): cv.use_id(cg.Switch),
}).extend(cv.COMPONENT_SCHEMA).extend(uart.UART_DEVICE_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await text_sensor.register_text_sensor(var, config)
    await uart.register_uart_device(var, config)
    
    switch = await cg.get_variable(config[CONF_SWITCH_ID])
    cg.add(var.set_privacy_switch(switch)) 