/**
  ******************************************************************************
  * miniSTM32.c
  * Brian
  * V0.1.0(based on ST version V4.5.0)
  * 06-July-2011
  ******************************************************************************
  */ 

#define PIEZO_INIT_PERIOD		(1000)
  
#include "miniSTM32_sio.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"

/**
  * Initialization of SIO board pepherals
  *		SIO_BTNn	: GPIO input / EXTI
  *		SIO_LED1	: GPIO output
  *		SIO_LED2	: TIM PWM output
  *		SIO_PIEZO	: TIM PWM output
  *		SIO_POT		: ADC input
  */

void miniSTM32_SIO_BoardInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	/* Enable the GPIO Clocks */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
		RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO, ENABLE);

	/**
	  * DI: Two push buttons connected to interrupt lines
	  *		SIO_BTN1 - PE2 - EXIN2
	  *		SIO_BTN2 - PE3 - EXIN3
	  */
	
	/* Configure SIO_BTN1 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	/* Connect Button EXTI Lines to SIO_BTN1 */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource2);

	/* Configure SIO_BTN1 EXTI line */
	EXTI_InitStructure.EXTI_Line = EXTI_Line2;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	/* Enable and set Button EXTI Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure); 
	
	/* Configure SIO_BTN2 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	/* Connect Button EXTI Lines to and SIO_BTN2 */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource3);
	
	/* Configure SIO_BTN2 EXTI line */
	EXTI_InitStructure.EXTI_Line = EXTI_Line3;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	/* Enable and set Button EXTI Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure); 

	/**
	  * DO: Two GPIO out
	  *		SIO_LED1 - PE4
	  *		SIO_LED2 - PB0
	  */

	/* Configure the PE4 pin */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	/* Configure the PB0 pin */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/*
	 * PWM OUT: Frequency control(1KHz - 10KHz) with 50% PWM
	 *		SIO_PIEZO - PA1 / TIM2_CH2
	 *		Base Freq: 1MHz = 72MHz / 72
	 *		ARR value: PERIOD = 1MHz / FREQ
	 *		CCR value: PULSE = PERIOD / 2 (always 50% PWM) 	
	 */

	/* Configure the PA1 pin */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Enable TIM2 clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	/* Configure TIM2 */
	TIM_TimeBaseStructure.TIM_Period = PIEZO_INIT_PERIOD;
	TIM_TimeBaseStructure.TIM_Prescaler = 72; /* 1MHz base clock */
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = (PIEZO_INIT_PERIOD>>1);
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM2, ENABLE);

	TIM_Cmd(TIM2, DISABLE);
	/**
	  * AI: ADC input
	  *		SIO_POT - ADC123_IN11
	  */
}

/**
  * Controls LEDs. Actual function depends on the type of control
  *		SIO_LED1 - GPIO: simple on/off
  *		SIO_LED2 - PWM: duty control
  */
void miniSTM32_SIO_LEDControl(uint16_t Led, uint16_t Duty)
{
}

void miniSTM32_SIO_LEDToggle(uint16_t Led)
{
	if(Led == SIO_LED1){
		GPIOE->ODR ^= GPIO_Pin_4;
	}
	else if(Led == SIO_LED2){
		GPIOB->ODR ^= GPIO_Pin_0;
	}
}

/**
  * Get current status of the button
  *
  */
void miniSTM32_SIO_PBGetState(uint16_t Button)
{
}

/**
  * Piezo PWM control
  */
void miniSTM32_SIO_PiezoControl(uint16_t Freq)
{
	uint16_t u16Period = 0;

	if( (Freq < MIN_PIEZO_FREQ) || (Freq > MAX_PIEZO_FREQ) ){
		/* Stop TIM2 */
		TIM_Cmd(TIM2, DISABLE);
	}
	else{
		/* Calculate required ARR value */
		u16Period = 1000000L / Freq;

		TIM_SetAutoreload(TIM2, u16Period);
		TIM_SetCompare2(TIM2, (u16Period>>1));

		/* Start TIM2 */
		TIM_Cmd(TIM2, ENABLE);
	}
}

/**
  * Read potentiomener (voltage) value
  */
uint16_t miniSTM32_SIO_POTGetValue(void)
{
	uint16_t value = 0;

	return value;
}

/* END OF FILE */

