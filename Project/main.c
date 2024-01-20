#include "RTE_Components.h"
#include CMSIS_device_header

#include "delay.h"
#include "led.h"
#include "key.h"

int main()
{
    led_init();
    key_init();

    for (;;)
    {
        if (1 == check_key())
        {
        led_trun();
        }
    }
}