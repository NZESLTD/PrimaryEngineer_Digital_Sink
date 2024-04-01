#ifndef CONTAINER_H
#define CONTAINER_H

class FlowMeter{
  public:

  // Instantaneous Flow Rate
  float coldFlowRate = 0;
  float hotFlowRate = 0;
  float wasteFlowRate = 0;

  // Total flow through each sensor
  unsigned long coldFlowTotal = 0;
  unsigned long hotFlowTotal = 0;
  unsigned long wasteFlowTotal = 0;

  // Total flow through system
  unsigned long totalIn = 0;
  //unsigned long totalOut = 0;

};

extern FlowMeter flowmeter;

#endif