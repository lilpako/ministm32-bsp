/*******************************************************************************
 * @file	miniSTM32.c
 * @author	Brian
 * @version	V0.1.0(based on ST version V4.5.0)
 * @date	06-July-2011
 */ 

  
#include "miniSTM32_sio.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"

/*
 * @brief	Initialization of SIO board pepherals:
 *		SIO_BTNn	: GPIO input / EXTI
 *		SIO_LED1	: GPIO output
 *		SIO_LED2	: TIM PWM output
 *		SIO_PIEZO	: TIM PWM output
 *		SIO_POT		: ADC input.
 * @param	None
 * @retval	None
 */
void SIO_Init(void)
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
		SIO_LED1_GPIO_CLK |
		SIO_LED2_GPIO_CLK |
		SIO_BTN1_GPIO_CLK |
		SIO_BTN2_GPIO_CLK |
		SIO_PZO_GPIO_CLK |
		SIO_POT_GPIO_CLK,
		ENABLE);

	/*
	 * DI: Two push buttons connected to interrupt lines
	 *		SIO_BTN1 - PE2 - EXIN2
	 *		SIO_BTN2 - PE3 - EXIN3
	 */
	
	/* Configure SIO_BTN1 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = SIO_BTN1_GPIO_PIN;
	GPIO_Init(SIO_BTN1_GPIO_PORT, &GPIO_InitStructure);

	/* Connect Button EXTI Lines to SIO_BTN1 */
	GPIO_EXTILineConfig(SIO_BTN1_EXTI_PORT, SIO_BTN1_EXTI_PIN);

	/* Configure SIO_BTN1 EXTI line */
	EXTI_InitStructure.EXTI_Line = SIO_BTN1_EXTI_LINE;
	EXTI_InitStructure.EXTI_Mode = SIO_BTN1_EXTI_MODE;
	EXTI_InitStructure.EXTI_Trigger = SIO_BTN1_EXTI_TRIG;  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	/* Enable and set Button EXTI Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel = SIO_BTN1_EXTI_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure); 
	
	/* Configure SIO_BTN2 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = SIO_BTN2_GPIO_PIN;
	GPIO_Init(SIO_BTN2_GPIO_PORT, &GPIO_InitStructure);
	
	/* Connect Button EXTI Lines to and SIO_BTN2 */
	GPIO_EXTILineConfig(SIO_BTN2_EXTI_PORT, SIO_BTN2_EXTI_PIN);
	
	/* Configure SIO_BTN2 EXTI line */
	EXTI_InitStructure.EXTI_Line = SIO_BTN2_EXTI_LINE;
	EXTI_InitStructure.EXTI_Mode = SIO_BTN2_EXTI_MODE;
	EXTI_InitStructure.EXTI_Trigger = SIO_BTN2_EXTI_TRIG;  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	/* Enable and set Button EXTI Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel = SIO_BTN2_EXTI_IRQn;
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
	GPIO_InitStructure.GPIO_Pin = SIO_LED1_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = SIO_GPIO_SPEED;
	GPIO_Init(SIO_LED1_GPIO_PORT, &GPIO_InitStructure);

	/* Configure the PB0 pin : output push-pull */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = SIO_LED2_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = SIO_GPIO_SPEED;
	GPIO_Init(SIO_LED2_GPIO_PORT, &GPIO_InitStructure);

	/*
	 * PWM OUT: Frequency control(1KHz - 10KHz) with 50% PWM
	 *		SIO_PZO - PA1 / TIM2_CH2
	 *		Base Freq: 1MHz = 72MHz / 72
	 *		ARR value: PERIOD = 1MHz / FREQ
	 *		CCR value: PULSE = PERIOD / 2 (always 50% PWM) 	
	 */

	/* Configure the PA1 pin : alternative push-pull */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = SIO_PZO_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = SIO_GPIO_SPEED;
	GPIO_Init(SIO_PZO_GPIO_PORT, &GPIO_InitStructure);

	/* Enable Pieze timer clock */
	RCC_APB1PeriphClockCmd(SIO_PZO_TIMER_CLK, ENABLE);

	/* Configure Piezo timer */
	TIM_TimeBaseStructure.TIM_Period = PIEZO_INIT_PERIOD;
	TIM_TimeBaseStructure.TIM_Prescaler = 72; /* 1MHz base clock */
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(SIO_PZO_TIMER, &TIM_TimeBaseStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = (PIEZO_INIT_PERIOD>>1);
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC2Init(SIO_PZO_TIMER, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(SIO_PZO_TIMER, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(SIO_PZO_TIMER, ENABLE);

	TIM_Cmd(SIO_PZO_TIMER, DISABLE);

	/*
	 * AI: ADC input
	 *		SIO_POT - PC1 / ADC123_IN11
	 */

	/* Configure the Potentiometer pin : analog input */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = SIO_POT_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = SIO_GPIO_SPEED;
	GPIO_Init(SIO_POT_GPIO_PORT, &GPIO_InitStructure);

	/* Configure Potentiometer ADC */
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_Init(SIO_POT_ADC, &ADC_InitStructure);
	ADC_RegularChannelConfig(SIO_POT_ADC, SIO_POT_ADC_CHN, 1, ADC_SampleTime_28Cycles5);
	ADC_ITConfig(SIO_POT_ADC, ADC_IT_EOC, ENABLE);

	/* Calibrate Potentiomenter ADC */
	ADC_Cmd(SIO_POT_ADC, ENABLE);
	ADC_ResetCalibration(SIO_POT_ADC);
	while(ADC_GetResetCalibrationStatus(SIO_POT_ADC));
	ADC_StartCalibration(SIO_POT_ADC);
	while(ADC_GetCalibrationStatus(SIO_POT_ADC));

}

/*
 * Turn on or off each LED
 *
 * Led: either SIO_LED1 or SIO_LED2
 *
 */

void SIO_LEDOn(SIO_LED_TypeDef Led)
{
	if(Led == SIO_LED1) {
		GPIOE->BSRR = SIO_LED1_GPIO_PIN;
	}
	else if(Led == SIO_LED2) {
		GPIOB->BSRR = SIO_LED2_GPIO_PIN;
	}
}

void SIO_LEDOff(SIO_LED_TypeDef Led)
{
	if(Led == SIO_LED1) {
		GPIOE->BRR = SIO_LED1_GPIO_PIN;
	}
	else if(Led == SIO_LED2) {
		GPIOB->BRR = SIO_LED2_GPIO_PIN;
	}
}

/*
 * Toggle LED
 *
 * Led: either SIO_LED1 or SIO_LED2
 */
void SIO_LEDToggle(SIO_LED_TypeDef Led)
{
	if(Led == SIO_LED1){
		SIO_LED1_GPIO_PORT->ODR ^= SIO_LED1_GPIO_PIN;
	}
	else if(Led == SIO_LED2){
		SIO_LED2_GPIO_PORT->ODR ^= SIO_LED2_GPIO_PIN;
	}
}

/*
 * Get status of LEDs
 *
 * Led: either SIO_LED1 or SIO_LED2
 * Return value: 0 means off, 0xffff error, otherwise on
 */
uint16_t SIO_LEDGetStatus(SIO_LED_TypeDef Led)
{
	if(Led == SIO_LED1)
		return((SIO_LED1_GPIO_PORT->IDR) & SIO_LED1_GPIO_PIN);
	else if(Led == SIO_LED2)
		return((SIO_LED2_GPIO_PORT->IDR) & SIO_LED2_GPIO_PIN);
	else return 0xffff;
}

/* Just let it be like this for now
void SIO_LEDPWMControl(SIO_LED_TypeDef Led, uint16_t Duty)
{
}
*/

/*
 * Get current status of the button
 *
 * Button: either SIO_BTN1 or SIO_BTN2
 * Return value: 0 means off, 0xffff error, otherwise on
 */
uint16_t SIO_PBGetState(SIO_Button_TypeDef Button)
{

	if(Button == SIO_BTN1)
		return((SIO_BTN1_GPIO_PORT->IDR) & SIO_BTN1_GPIO_PIN);
	else if(Button == SIO_BTN2)
		return((SIO_BTN2_GPIO_PORT->IDR) & SIO_BTN2_GPIO_PIN);
	else return 0xffff;
}

/*
 * Piezo PWM control, duty is always 50 %
 *
 * Freq: PWM drive frequency, it should be between MIN_PIEZO_FREQ and 
 *       MAX_PIEZO_FREQ to make corresponding output. others to turn off
 *
 */
void SIO_PiezoControl(uint16_t Freq)
{
	uint16_t u16Period = 0;

	if( (Freq < MIN_PIEZO_FREQ) || (Freq > MAX_PIEZO_FREQ) ){
		/* Stop Piezo timer */
		TIM_Cmd(SIO_PZO_TIMER, DISABLE);
	}
	else{
		/* Calculate required ARR value */
		u16Period = 1000000L / Freq;

		TIM_SetAutoreload(SIO_PZO_TIMER, u16Period);
		TIM_SetCompare2(SIO_PZO_TIMER, (u16Period>>1));

		/* Start TIM2 */
		TIM_Cmd(SIO_PZO_TIMER, ENABLE);
	}
}

/*
 * Read potentiomener (voltage?) value
 *
 * Output should be between 0(min) and 2^12-1 = 4097(max)
 */
uint16_t SIO_POTGetValue(void)
{

	ADC_SoftwareStartConvCmd(SIO_POT_ADC, ENABLE);

	while(ADC_GetSoftwareStartConvStatus(SIO_POT_ADC));

	return ADC_GetConversionValue(SIO_POT_ADC);

}

/* END OF FILE */

