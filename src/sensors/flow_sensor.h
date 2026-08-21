#ifndef FLOW_SENSOR_H
#define FLOW_SENSOR_H

#include "../../include/types.h"

void flow_sensor_init(void);
uint32_t flow_sensor_get_pulse_count(void);
void flow_sensor_set_pulse_count(uint32_t count);
float flow_sensor_get_total_volume(void);
float flow_sensor_get_flow_rate(uint32_t sample_period_ms);
void flow_sensor_reset(void);

#endif /* FLOW_SENSOR_H */
