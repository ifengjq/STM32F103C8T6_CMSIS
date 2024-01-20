#include "key.h"
#include "delay.h"

/**
 * @brief key GPIOA_Pin_0  init
 *
 */
void key_init(void)
{
    GPIO_InitTypeDef gpio_init_structure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    gpio_init_structure.GPIO_Mode = GPIO_Mode_IPU;
    gpio_init_structure.GPIO_Pin = GPIO_Pin_0;
    gpio_init_structure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &gpio_init_structure);
}

/**
 * @brief 检查按键是否被按下
 * 
 * @return uint8_t 返回按键是否被按下的状态
 */
uint8_t check_key(void)
{
    uint8_t status = 0;

    if (0 == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))
    {
        delay_ms(20);
        for (; 0 == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);)
        {
        }
        delay_ms(20);

        status = 1;
    }

    return status;
}