#include <Arduino.h>
#include "flow_sensor.h"

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

  // Attach an Interrupt to the flow meter pin
  attachInterrupt(digitalPinToInterrupt(flowSensorPin), pulseCounter, FALLING);

}

float loop_flow_sensor(const char* flowID){
  static float flowRate;

  // Reset pulse count and flow duration
  pulseCount = 0;
  interrupts(); // Enable interrupts
  delay(1000);  // Wait for one second to count pulses
  noInterrupts(); // Disable interrupts to avoid interference with pulse co

  // Flow Rate Calculations
  // Need to confirm ML / pulse with actual sensor from amazon
  flowRate = (pulseCount * 0.45); // pulse count * ml/pulse (total flow per second)
  flowRate = (flowRate * 60); // Flow Rate per minute
  flowRate = flowRate / 1000; // Flow Rate in Litres/min

  String idMessage = String(flowID) + " - Flow Rate:";
  Serial.print(idMessage);
  Serial.println(flowRate);
  Serial.print(" L/min");

  return flowRate;
}