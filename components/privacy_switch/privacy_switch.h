#pragma once

#include "esphome/core/component.h"
#include "esphome/components/switch/switch.h"
#include "esphome/components/uart/uart.h"

namespace esphome {
namespace privacy_switch {

class PrivacySwitch : public switch_::Switch, public Component {
 public:
  void set_uart_parent(uart::UARTComponent *parent) { uart_parent_ = parent; }

  void setup() override {
    // nothing to do here
  }

  void dump_config() override {
    ESP_LOGCONFIG(TAG, "Privacy Switch:");
    LOG_SWITCH("  ", "State", this);
  }

  void write_state(bool state) override {
    this->publish_state(state);
    if (state) {
      uart_parent_->write_str("Privacy Switch: ON\n");
      ESP_LOGD(TAG, "Privacy Switch: ON");
    } else {
      uart_parent_->write_str("Privacy Switch: OFF\n");
      ESP_LOGD(TAG, "Privacy Switch: OFF");
    }
  }

  void loop() override {
    if (!uart_parent_->available())
      return;

    uint8_t c;
    while (uart_parent_->read_byte(&c)) {
      if (c == '\n' || c == '\r') {
        if (buffer_.length() > 0) {
          process_line_();
          buffer_.clear();
        }
        continue;
      }
      buffer_ += (char)c;
    }
  }

 protected:
  void process_line_() {
    if (buffer_ == "GET_STATE") {
      bool state = this->state;
      uart_parent_->write_str(("STATE:" + std::string(state ? "ON" : "OFF") + "\n").c_str());
    } else if (buffer_ == "ACK:ON" && !this->state) {
      this->turn_on();
    } else if (buffer_ == "ACK:OFF" && this->state) {
      this->turn_off();
    }
  }

  static const char *const TAG = "privacy_switch";
  uart::UARTComponent *uart_parent_{nullptr};
  std::string buffer_;
};

}  // namespace privacy_switch
}  // namespace esphome 