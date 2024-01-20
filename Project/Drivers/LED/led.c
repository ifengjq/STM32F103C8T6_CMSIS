#include "led.h"

/**
 * @brief LED GPIOC_Pin_13  init
 *
 */
void led_init(void)
{
    GPIO_InitTypeDef gpio_init_structure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    gpio_init_structure.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio_init_structure.GPIO_Pin = GPIO_Pin_13;
    gpio_init_structure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOC, &gpio_init_structure);

    GPIO_SetBits(GPIOC, GPIO_Pin_13);
}

/**
 * @brief 翻转当前 LED 的状态
 * 
 * @return uint8_t 翻转后的 LED 状态
 */
uint8_t led_trun(void)
{
    if (1 == GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13))
    {
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);
    }
    else if (0 == GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13))
    {
        GPIO_SetBits(GPIOC, GPIO_Pin_13);
    }

    return GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13);
}

/**
 * @brief 切换 LED 的开启状态
 * 
 * @param status led 的期望状态
 * @return uint8_t led 当前的状态
 */
uint8_t led_switch(uint8_t status)
{
    if (1 == status)
    {
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);
    }
    else
    {
        GPIO_SetBits(GPIOC, GPIO_Pin_13);
    }

    return GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13);
}