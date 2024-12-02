#include "esphome.h"
#include "gree_versati.h"

class GreeVersatiClimateComponent : public PollingComponent {
 public:
  GreeVersatiClimateComponent() : PollingComponent(60000) {}

  void setup() override {
    ESP_LOGCONFIG(TAG, "Setting up Gree Versati Climate Component...");
    climate_ = new GreeVersatiClimate();
    App.register_component(climate_);
  }

  void update() override {
    climate_->update_state();
  }

 private:
  GreeVersatiClimate *climate_;
};