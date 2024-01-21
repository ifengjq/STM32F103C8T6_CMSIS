#ifndef __ENCODER_H
#define __ENCODER_H

#include "stm32f10x.h"

void encoder_init(void);
int16_t get_encoder_value_0(void);
int16_t get_encoder_value_1(void);

#endif