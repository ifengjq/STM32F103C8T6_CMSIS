#include "encoder.h"

static int16_t s_encoder_value_0 = 0;
static int16_t s_encoder_value_1 = 0;

void encoder_init(void)
{
    GPIO_InitTypeDef gpio_init_structure;
    EXTI_InitTypeDef exti_init_structure;
    NVIC_InitTypeDef nvic_init_structure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    gpio_init_structure.GPIO_Mode = GPIO_Mode_IPU;
    gpio_init_structure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    gpio_init_structure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &gpio_init_structure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);

    exti_init_structure.EXTI_Line = EXTI_Line0 | EXTI_Line1;
    exti_init_structure.EXTI_LineCmd = ENABLE;
    exti_init_structure.EXTI_Mode = EXTI_Mode_Interrupt;
    exti_init_structure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_Init(&exti_init_structure);

    nvic_init_structure.NVIC_IRQChannel = EXTI0_IRQn;
    nvic_init_structure.NVIC_IRQChannelCmd = ENABLE;
    nvic_init_structure.NVIC_IRQChannelPreemptionPriority = 1;
    nvic_init_structure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&nvic_init_structure);

    nvic_init_structure.NVIC_IRQChannel = EXTI1_IRQn;
    nvic_init_structure.NVIC_IRQChannelCmd = ENABLE;
    nvic_init_structure.NVIC_IRQChannelPreemptionPriority = 1;
    nvic_init_structure.NVIC_IRQChannelSubPriority = 2;
    NVIC_Init(&nvic_init_structure);
}

int16_t get_encoder_value_0(void)
{
    return s_encoder_value_0;
}

int16_t get_encoder_value_1(void)
{
    return s_encoder_value_1;
}

/**
 * @brief encoder 逆时针旋转: A 下降沿 && B 低电平
 * 
 */
void EXTI0_IRQHandler(void)
{
    if (SET == EXTI_GetITStatus(EXTI_Line0))
    {
        if (RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1))
        {
            s_encoder_value_0 += 1;
        }
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}

/**
 * @brief encoder 顺时针旋转: B 下降沿 && A 低电平
 * 
 */
void EXTI1_IRQHandler(void)
{
    if (SET == EXTI_GetITStatus(EXTI_Line1))
    {
        if (RESET == GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1))
        {
            s_encoder_value_1 += 1;
        }

        EXTI_ClearITPendingBit(EXTI_Line1);
    }
}