#pragma once

#include "esphome.h"
#include "esphome/components/modbus_controller/modbus_controller.h"

namespace esphome {
namespace gree_versati {

class GreeVersati : public PollingComponent {
 public:
  explicit GreeVersati() : PollingComponent(30000) {}  // Default 30s polling interval

  void setup() override;
  void update() override;

  void set_modbus_controller(modbus_controller::ModbusController *controller) {
    this->modbus_controller_ = controller;
  }

 protected:
  modbus_controller::ModbusController *modbus_controller_{nullptr};

  // Sensor creation helpers
  void create_sensor(const char *name, int address, float multiplier = 1.0);
  void create_number(const char *name, int address, float min, float max, float step, float multiplier = 1.0);
  void create_select(const char *name, int address, const std::map<std::string, int> &options);
  void create_text_sensor(const char *name, int address, const std::map<int, std::string> &modes);

  int16_t read_modbus_register(int address);
};

}  // namespace gree_versati
}  // namespace esphome
