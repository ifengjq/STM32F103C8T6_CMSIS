#include "RTE_Components.h"
#include CMSIS_device_header

#include "delay.h"
#include "led.h"
#include "key.h"
#include "oled.h"

int main()
{
    oled_init();
    led_init();
    key_init();

    oled_show_string(1, 1, "Hello World!");

    for (;;)
    {
        if (1 == check_key())
        {
        led_trun();
        }
    }
}