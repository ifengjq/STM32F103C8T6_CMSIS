#include "count_sensor.h"

static uint16_t s_count = 0;

void count_sensor_init(void)
{
    GPIO_InitTypeDef gpio_init_structure;
    EXTI_InitTypeDef exti_init_structure;
    NVIC_InitTypeDef nvic_init_structure;

    // 1. 初始化外设时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    // 初始化 GPIO
    gpio_init_structure.GPIO_Mode = GPIO_Mode_IPU;
    gpio_init_structure.GPIO_Pin = GPIO_Pin_14;
    gpio_init_structure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &gpio_init_structure);

    // 选择 GPIOB_14 中断通道
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);

    // EXTI 中断配置
    exti_init_structure.EXTI_Line = EXTI_Line14;
    exti_init_structure.EXTI_Mode = EXTI_Mode_Interrupt;
    exti_init_structure.EXTI_Trigger = EXTI_Trigger_Falling;
    exti_init_structure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&exti_init_structure);

    nvic_init_structure.NVIC_IRQChannel = EXTI15_10_IRQn;
    // 抢占优先级，可以抢占响应优先级的中断
    nvic_init_structure.NVIC_IRQChannelPreemptionPriority = 1;
    // 响应优先级
    nvic_init_structure.NVIC_IRQChannelSubPriority = 1;
    nvic_init_structure.NVIC_IRQChannelCmd = ENABLE;

    // 在 main() 配置 NVIC，全局有效，只能配置一次

    NVIC_Init(&nvic_init_structure);
}

uint16_t get_count(void)
{
    return s_count;
}

/**
 * @brief 中断处理函数
 * 
 */
void EXTI15_10_IRQHandler(void)
{
    if (SET == EXTI_GetITStatus(EXTI_Line14))
    {
        s_count += 1;
        EXTI_ClearITPendingBit(EXTI_Line14);
    }
}