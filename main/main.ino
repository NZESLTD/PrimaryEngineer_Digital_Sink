// Include Paths
#include <Arduino.h>
#include "flow_sensor.h"

/// Run once on startupd:\User Files\Documents\_personal_projects\Thales_Primary_Engineer_Digital_Sink\PrimaryEngineer_Digital_Sink\flow_sensor.cpp
void setup() {
  Serial.begin(9600);
  Serial.println("... Start-up ...");

  // Init Flow Sensors
  start_flow_sensor();
}

/// Loop Continuously
void loop() {
  unsigned long currentMillis = millis();

  static float coldWaterFlow, hotWaterFlow, sinkWasteFlow;
  
  // Read flow sensor values
  loop_flow_sensor(currentMillis);

  // Read Sink Level
  // sinkWasteFlow = loop_flow_sensor("SinkWaste");

  //    Either Drain flow sensor / ultrasonic
  // Update display
}
