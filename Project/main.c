#include "RTE_Components.h"
#include CMSIS_device_header

#include "delay.h"
#include "led.h"
#include "key.h"
#include "oled.h"
#include "count_sensor.h"
#include "encoder.h"

int main()
{
    led_init();
    key_init();
    oled_init();
    count_sensor_init();
    encoder_init();

    // 配置 NVIC，全局有效，只能配置一次
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    oled_show_string(1, 1, "STM32F103C8T6");
    oled_show_string(2, 1, "Count: ");
    oled_show_string(3, 1, "Encoder+: ");
    oled_show_string(4, 1, "Encoder-: ");

    for (;;)
    {
        oled_show_num(2, 8, get_count(), 5);
        oled_show_signed_num(3, 10, get_encoder_value_0(), 5);
        oled_show_signed_num(4, 10, get_encoder_value_1(), 5);
        if (1 == check_key())
        {
            led_trun();
        }
    }
}