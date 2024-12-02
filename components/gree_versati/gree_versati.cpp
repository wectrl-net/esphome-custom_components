#include "gree_versati.h"

namespace esphome {
namespace gree_versati {

void GreeVersati::setup() {
  ESP_LOGCONFIG(TAG, "Setting up Gree Versati custom component...");

  if (this->modbus_controller_ == nullptr) {
    ESP_LOGE(TAG, "Modbus controller not set. Cannot proceed.");
    return;
  }

  // Sensors
  create_sensor("Heatpump - Outdoor Temp", 118, 1.0);
  create_sensor("Heatpump - Defrost Temp", 119, 1.0);
  create_sensor("Heatpump - Outdoor Discharge Temp", 120, 1.0);
  create_sensor("Heatpump - Outdoor Suction Temp", 121, 1.0);
  create_sensor("Heatpump - Plate Exchanger Water-Out Temp", 122, 0.1);
  create_sensor("Heatpump - E-heater Leaving Water Temp", 123, 0.1);
  create_sensor("Heatpump - Liquid Line Temp", 124, 1.0);
  create_sensor("Heatpump - Plate Exchanger Water-In Temp", 125, 0.1);
  create_sensor("Heatpump - Water Tank Temp Sensor 1", 126, 1.0);
  create_sensor("Heatpump - Water Tank Temp Sensor 2", 127, 1.0);

  // Numbers
  create_number("Heatpump - Ambient Temp Upper Limit for Heating", 17, 10, 37, 1);
  create_number("Heatpump - Ambient Temp Lower Limit for Heating", 18, -22, 5, 1);
  create_number("Heatpump - Temp Deviation for Heating", 30, 2, 10, 1);
  create_number("Heatpump - Sanitizing Temperature", 4, 40, 70, 1);
  create_number("Heatpump - Floor Debug Section", 5, 1, 10, 1);
  create_number("Heatpump - First Floor Debug Temperature", 6, 25, 35, 1);
  create_number("Heatpump - Each Floor Debug Temperature", 7, 2, 10, 1);
  create_number("Heatpump - Each Floor Debug Interval", 8, 0, 72, 1);
  create_number("Heatpump - Leaving Water Temp for Cooling", 9, 7, 25, 1);
  create_number("Heatpump - Leaving Water Temp for Heating", 10, 25, 63, 1);
  create_number("Heatpump - Indoor Temp Set Point for Cooling", 11, 18, 30, 1);
  create_number("Heatpump - Indoor Temp Set Point for Heating", 12, 18, 30, 1);
  create_number("Heatpump - Water Tank Temp", 13, 40, 80, 1);

  // Selects
  create_select("Heatpump - Thermostat", 42, {{"Without", 0}, {"Air", 1}, {"Air + Hot Water", 2}});
  create_select("Heatpump - On/Off", 1, {{"Off", 0x55}, {"On", 0xAA}});
  create_select("Heatpump - Mode Setting", 2, {{"Heat", 1}, {"Hot water", 2}, {"Cool + Hot water", 3}, {"Heat + Hot water", 4}, {"Cool", 5}});
  create_select("Heatpump - E-heater Control", 3, {{"1 set", 1}, {"2 sets", 2}, {"Off", 3}});

  // Text sensor
  create_text_sensor("Heatpump - Outdoor Unit Mode", 117, {{1, "Cool"}, {2, "Heat"}, {6, "Hot water"}, {8, "Off"}});
}

void GreeVersati::update() {
  ESP_LOGCONFIG(TAG, "Updating Gree Versati sensors...");
  // Implement update logic by reading Modbus registers
}

void GreeVersati::create_sensor(const char *name, int address, float multiplier) {
  auto *s = new sensor::Sensor();
  s->set_name(name);
  // Link sensor to Modbus register
}

void GreeVersati::create_number(const char *name, int address, float min, float max, float step, float multiplier) {
  auto *n = new number::Number();
  n->set_name(name);
  n->set_min_value(min);
  n->set_max_value(max);
  n->set_step(step);
  // Link number to Modbus register
}

void GreeVersati::create_select(const char *name, int address, const std::map<std::string, int> &options) {
  auto *sel = new select::Select();
  sel->set_name(name);
  // Link select to Modbus register
}

void GreeVersati::create_text_sensor(const char *name, int address, const std::map<int, std::string> &modes) {
  auto *ts = new text_sensor::TextSensor();
  ts->set_name(name);
  // Link text sensor to Modbus register
}

int16_t GreeVersati::read_modbus_register(int address) {
  if (this->modbus_controller_ != nullptr) {
    return this->modbus_controller_->read_holding_register(address);
  }
  ESP_LOGE(TAG, "Modbus controller not set. Cannot read register.");
  return 0;
}

}  // namespace gree_versati
}  // namespace esphome
