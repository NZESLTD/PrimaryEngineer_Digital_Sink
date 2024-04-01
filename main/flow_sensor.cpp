#include <Arduino.h>
#include "flow_sensor.h"
#include "container.h"

/// For Knowledge:
// https://arduino.stackexchange.com/questions/83702/adding-another-flow-sensor-to-sketch

// Pin-outs
const int coldFlowPin = 2;
const int hotFlowPin = 3;
const int wasteFlowPin = 4;

// Define variables for the flow rate
volatile unsigned int coldFlowCtr, hotFlowCtr, wasteFlowCtr;

void coldFlowPulseCtr(){
  coldFlowCtr++;
}

void hotFlowPulseCtr(){
  hotFlowCtr++;
}

void wasteFlowPulseCtr(){
  wasteFlowCtr++;
}

void start_flow_sensor(){
  Serial.println("... Flow Sensor Init ...");

  // Initialise the Flow Meter
  pinMode(coldFlowPin, INPUT_PULLUP);
  pinMode(hotFlowPin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(coldFlowPin), coldFlowPulseCtr, FALLING);
  attachInterrupt(digitalPinToInterrupt(hotFlowPin), hotFlowPulseCtr, FALLING);
  attachInterrupt(digitalPinToInterrupt(wasteFlowPin), wasteFlowPulseCtr, FALLING);
}

float loop_flow_sensor(unsigned long &currentMillis){
  static unsigned long previousRead = 0;
  static uint8_t prevColdFlowCtr, prevHotFlowCtr, prevWasteFlowCtr;

  // Check if one second has elapsed since the last measurement
  if (currentMillis - previousRead >= 1000) {
    // NOTE: Using uint8_t flowrate cannot exceed 33.7L/min, use uint16_t for above
    // Update delta pulse counts

    // Cold Water
    uint8_t newColdCtr = coldFlowCtr;  // atomic read
    uint8_t deltaColdFlowCtr = newColdCtr - prevColdFlowCtr;
    // Calculate Flow Rate
    flowmeter.coldFlowRate = (deltaColdFlowCtr * 0.45); // pulse count * ml/pulse (total flow per second)
    flowmeter.coldFlowTotal += flowmeter.coldFlowRate; // Total mL used
    flowmeter.coldFlowRate = (flowmeter.coldFlowRate * 60); // Flow Rate per minute
    flowmeter.coldFlowRate = flowmeter.coldFlowRate / 1000; // Flow Rate in Litres/min

    Serial.println("Cold Flow Rate:");
    Serial.print(flowmeter.coldFlowRate);
    Serial.println(" L/min");
    Serial.println("");

    prevColdFlowCtr = newColdCtr;

    
    // Hot Water
    uint8_t newHotCtr = hotFlowCtr;  // atomic read
    uint8_t deltaHotFlowCtr = newHotCtr - prevHotFlowCtr;
    // Calculate Flow Rate
    flowmeter.hotFlowRate = (deltaHotFlowCtr * 0.45); // pulse count * ml/pulse (total flow per second)
    flowmeter.hotFlowTotal += flowmeter.hotFlowRate; // Total mL used
    flowmeter.hotFlowRate = (flowmeter.hotFlowRate * 60); // Flow Rate per minute
    flowmeter.hotFlowRate = flowmeter.hotFlowRate / 1000; // Flow Rate in Litres/min

    Serial.println("Hot Flow Rate:");
    Serial.print(flowmeter.hotFlowRate);
    Serial.println(" L/min");
    Serial.println("");

    prevHotFlowCtr = newHotCtr;


    // Waste Water
    uint8_t newWasteCtr = wasteFlowCtr;  // atomic read
    uint8_t deltaWasteFlowCtr = newWasteCtr - prevWasteFlowCtr;
    // Calculate Flow Rate
    flowmeter.wasteFlowRate = (deltaWasteFlowCtr * 0.45); // pulse count * ml/pulse (ml/sec)
    flowmeter.wasteFlowTotal += flowmeter.wasteFlowRate; // Total ml used
    flowmeter.wasteFlowRate = (flowmeter.wasteFlowRate * 60); // Flow Rate per minute
    flowmeter.wasteFlowRate = flowmeter.wasteFlowRate / 1000; // Flow Rate in Litres/min

    Serial.println("Waste Flow Rate:");
    Serial.print(flowmeter.wasteFlowRate);
    Serial.println(" L/min");
    Serial.println("");

    prevWasteFlowCtr = newWasteCtr;

    Serial.println("");
    Serial.println("Total Flow In: ");
    flowmeter.totalIn = flowmeter.coldFlowTotal + flowmeter.hotFlowTotal;
    Serial.println(" mL");
    Serial.println("");

    Serial.println("Total Flow Out: ");
    Serial.print(flowmeter.wasteFlowTotal);
    Serial.println(" mL");


    // Update previousRead
    previousRead = currentMillis;
  }
}