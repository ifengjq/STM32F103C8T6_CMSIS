#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

void led_init(void);
uint8_t led_switch(uint8_t status);
uint8_t led_trun(void);

#endif