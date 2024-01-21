#ifndef __COUNT_SENSOR_H
#define __COUNT_SENSOR_H

#include "stm32f10x.h"

void count_sensor_init(void);
uint16_t get_count(void);

#endif