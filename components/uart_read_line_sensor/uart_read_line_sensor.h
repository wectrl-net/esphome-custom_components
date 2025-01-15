 #pragma once

#include "esphome.h"
#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/switch/switch.h"

namespace esphome {
namespace uart_read_line_sensor {

class UartReadLineSensor : public Component, public uart::UARTDevice, public text_sensor::TextSensor {
 public:
  void set_privacy_switch(switch_::Switch *privacy_switch) { privacy_switch_ = privacy_switch; }

  void setup() override {
    // nothing to do here
  }

  void process_message(const std::string &message) {
    if (message == "GET_STATE") {
      bool state = privacy_switch_->state;
      this->write_str(("STATE:" + std::string(state ? "ON" : "OFF") + "\n").c_str());
    } else if (message.find("ACK:") != std::string::npos) {
      if (message == "ACK:ON" && !privacy_switch_->state) {
        privacy_switch_->turn_on();
      } else if (message == "ACK:OFF" && privacy_switch_->state) {
        privacy_switch_->turn_off();
      }
    }
  }

  int readline(int readch, char *buffer, int len) {
    static int pos = 0;
    int rpos;

    if (readch > 0) {
      switch (readch) {
        case '\n':
        case '\r':
          buffer[pos] = 0;
          rpos = pos;
          pos = 0;
          return rpos;
        default:
          if ((pos < len-1) && (readch < 127)) {
            buffer[pos++] = readch;
            buffer[pos] = 0;
          } else {
            buffer[pos] = 0;
            rpos = pos;
            pos = 0;
            return rpos;
          }
      }
    }
    return -1;
  }

  void loop() override {
    const int max_line_length = 80;
    static char buffer[max_line_length];
    while (available()) {
      if(readline(read(), buffer, max_line_length) > 0) {
        std::string message = buffer;
        publish_state(message);
        process_message(message);
      }
    }
  }

 private:
  switch_::Switch *privacy_switch_{nullptr};
};

}  // namespace uart_read_line_sensor
}  // namespace esphome 