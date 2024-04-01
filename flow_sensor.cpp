#include <Arduino.h>
#include "flow_sensor.h"

/// For Knowledge:
// https://arduino.stackexchange.com/questions/83702/adding-another-flow-sensor-to-sketch

// Define variables for the flow rate
volatile unsigned int pulseCount;

void pulseCounter(){
  pulseCount++;
}

void start_flow_sensor(const int &flowSensorPin, const char* flowID){
  String idMessage = "... Flow Sensor " + String(flowID) + " Init ...";
  Serial.println(idMessage);

  // Initialise the Flow Meter
  pinMode(flowSensorPin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(flowSensorPin), pulseCounter, FALLING);
}

float loop_flow_sensor(const char* flowID){
  static uint8_t oldPulseCount = 0;
  static float flowRate = 0;
  static unsigned long previousRead = 0;

  // Check if one second has elapsed since the last measurement
  unsigned long currentMillis = millis();
  if (currentMillis - previousRead >= 1000) {
    // NOTE: Using uint8_t flowrate cannot exceed 33.7L/min, use uint16_t for above
    uint8_t newPulseCount = pulseCount;
    uint8_t pulseCountDifference = newPulseCount - oldPulseCount;
    oldPulseCount = newPulseCount;

    // Reset pulse count and flow duration
    flowRate = (pulseCount * 0.45); // pulse count * ml/pulse (total flow per second)
    flowRate = (flowRate * 60); // Flow Rate per minute
    flowRate = flowRate / 1000; // Flow Rate in Litres/min

    String idMessage = String(flowID) + " - Flow Rate:";
    Serial.print(idMessage);
    Serial.println(flowRate);
    Serial.print(" L/min");

    // Reset pulse count and update previousRead
    pulseCount = 0;
    previousRead = currentMillis;
  }

  return flowRate;
}