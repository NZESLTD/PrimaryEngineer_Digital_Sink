// Include Paths
#include <Arduino.h>
#include "flow_sensor.h"

// Pin-outs
const int coldFlowPin = 2;
const int warmFlowPin = 3;
const int returnFlowPin = 4;
const int ultraSonicPin = 5;

/// Run once on startup
void setup() {
  Serial.begin(9600);
  Serial.println("... Start-up ...");

  // Initialise Flow Sensors
  // Cold water intake
  start_flow_sensor(coldFlowPin, "ColdWater");
  // Hot water intake
  start_flow_sensor(warmFlowPin, "HotWater");
  // Return Flow
  start_flow_sensor(returnFlowPin, "SinkWaste");
}

/// Loop Continuously
void loop() {
  static float coldWaterFlow, hotWaterFlow, sinkWasteFlow;
  
  // Read both intake flow sensor values
  coldWaterFlow = loop_flow_sensor("ColdWater");
  hotWaterFlow = loop_flow_sensor("HotWater");

  // Read Sink Level
  sinkWasteFlow = loop_flow_sensor("SinkWaste");

  //    Either Drain flow sensor / ultrasonic
  // Update display
}
