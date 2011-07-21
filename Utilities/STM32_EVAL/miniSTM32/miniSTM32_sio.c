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

/*
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
	ADC_InitTypeDef ADC_InitStructure;

	/*
	 * Common to all: Enable the GPIO Clocks 
	 */
	RCC_APB2PeriphClockCmd(
//		RCC_APB2Periph_GPIOA | 
		RCC_APB2Periph_GPIOB |			// LED output
//		RCC_APB2Periph_GPIOC |
		RCC_APB2Periph_GPIOE |			// button inputs, LED output
		RCC_APB2Periph_ADC1 |			// potentiometer
		RCC_APB2Periph_AFIO, ENABLE);	// piezo buzzer

	/*
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

	/*
	 * DO: Two GPIO out
	 *		SIO_LED1 - PE4
	 *		SIO_LED2 - PB0
	 */

	/* Configure the PE4 pin : output push-pull */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	/* Configure the PB0 pin : output push-pull */
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

	/* Configure the PA1 pin : alternative push-pull */
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

	/*
	 * AI: ADC input
	 *		SIO_POT - PC1 / ADC123_IN11
	 */

	/* Configure the PC1 pin : analog input */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* Configure ADC1_IN11 */
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_Init(ADC1, &ADC_InitStructure);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 1, ADC_SampleTime_28Cycles5);
	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);

	/* Calibrate ADC1 */
	ADC_Cmd(ADC1, ENABLE);
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));

}

/*
 * Turn on or off each LED
 *
 * Led: either SIO_LED1 or SIO_LED2
 * Flag: O to turn off the LED, others to turn on
 *
 *		SIO_LED1 - GPIOE.Pin4
 *		SIO_LED2 - GPIOB.Pin0
 */
void miniSTM32_SIO_LEDControl(uint16_t Led, uint16_t Flag)
{
	if(Led == SIO_LED1) {
		if(Flag) GPIOE->BSRR = GPIO_Pin_4;
		else GPIOE->BRR = GPIO_Pin_4;
	}
	else if(Led == SIO_LED2) {
		if(Flag) GPIOB->BSRR = GPIO_Pin_0;
		else GPIOB->BRR = GPIO_Pin_0;
	}
}

/*
 * Toggle LED
 *
 * Led: either SIO_LED1 or SIO_LED2
 */
void miniSTM32_SIO_LEDToggle(uint16_t Led)
{
	if(Led == SIO_LED1){
		GPIOE->ODR ^= GPIO_Pin_4;
	}
	else if(Led == SIO_LED2){
		GPIOB->ODR ^= GPIO_Pin_0;
	}
}

/*
 * Get status of LEDs
 *
 * Led: either SIO_LED1 or SIO_LED2
 * Return value: 0 means off, otherwise on
 */
uint16_t miniSTM32_SIO_LEDGetStatus(uint16_t Led)
{
	if(Led == SIO_LED1)
		return((GPIOE->IDR) & GPIO_Pin_4);
	else if(Led == SIO_LED2)
		return((GPIOB->IDR) & GPIO_Pin_0);
	else return 0;
}

/* Just let it be like this for now
void miniSTM32_SIO_LEDPWMControl(uint16_t Led, uint16_t Duty)
{
}
*/

/*
 * Get current status of the button
 *
 * Button: either SIO_BTN1 or SIO_BTN2
 * Return value: 0 means off, otherwise on
 */
uint16_t miniSTM32_SIO_ButtonGetState(uint16_t Button)
{

	if(Button == SIO_BTN1)
		return((GPIOE->IDR) & GPIO_Pin_2);
	else if(Button == SIO_BTN2)
		return((GPIOE->IDR) & GPIO_Pin_3);
	else return 0;
}

/*
 * Piezo PWM control, duty is always 50 %
 *
 * Freq: PWM drive frequency, it should be between MIN_PIEZO_FREQ and 
 *       MAX_PIEZO_FREQ to make corresponding output. others to turn off
 *
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

/*
 * Read potentiomener (voltage?) value
 *
 * Output should be between 0(min) and 2^12-1 = 4097(max)
 */
uint16_t miniSTM32_SIO_POTGetValue(void)
{

	ADC_SoftwareStartConvCmd(ADC1, ENABLE);

	while(ADC_GetSoftwareStartConvStatus(ADC1));

	return ADC_GetConversionValue(ADC1);

}

/* END OF FILE */

