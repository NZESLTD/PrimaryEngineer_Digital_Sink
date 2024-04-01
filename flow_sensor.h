#ifndef FLOW_SENSOR_H
#define FLOW_SENSOR_H

void start_flow_sensor(const int &flowSensorPin, const char* flowID);
float loop_flow_sensor(const char* flowID);

#endif
