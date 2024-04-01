#ifndef FLOW_SENSOR_H
#define FLOW_SENSOR_H

#define ColdWaterID 1
#define HotWaterID 2
#define SinkWasteID 3

void start_flow_sensor(const int &flowSensorPin, const char* flowID);
float loop_flow_sensor(const char* flowID);

#endif
