/*******************************************************************************
 * @file	Project/LCDDemo/system_stm32f10x.c
 * @author  Brian
 * @version V0.2.0
 * @date    08-August-2011
 * @brief   CMSIS Cortex-M3 Device Peripheral Access Layer System Source File.
 *			Majority part of this file comes from the examples of the ST 
 *			Peripheral Library V3.5.0
 */

#include "stm32f10x.h"

#define SYSCLK_FREQ_72MHz  72000000
/* 
#define VECT_TAB_SRAM 
*/
#define VECT_TAB_OFFSET  0x0 /* Vector Table base offset.  A multiple of 0x200. */

/*******************************************************************************
*  Clock Definitions
*******************************************************************************/
uint32_t SystemCoreClock = SYSCLK_FREQ_72MHz;

__I uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

static void SetSysClock(void);
static void SetSysClockTo72(void);

void SystemInit (void)
{
  /* Reset the RCC clock configuration to the default reset state */
  /* Set HSION bit */
  RCC->CR |= (uint32_t)0x00000001;

  /* Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits */
  RCC->CFGR &= (uint32_t)0xF0FF0000;
  
  /* Reset HSEON, CSSON and PLLON bits */
  RCC->CR &= (uint32_t)0xFEF6FFFF;

  /* Reset HSEBYP bit */
  RCC->CR &= (uint32_t)0xFFFBFFFF;

  /* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits */
  RCC->CFGR &= (uint32_t)0xFF80FFFF;

  /* Disable all interrupts and clear pending bits  */
  RCC->CIR = 0x009F0000;
    
  /* Configure the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers */
  /* Configure the Flash Latency cycles and enable prefetch buffer */
  SetSysClock();

#ifdef VECT_TAB_SRAM
  /* Vector Table Relocation in Internal SRAM. */
  SCB->VTOR = SRAM_BASE | VECT_TAB_OFFSET; 
#else
  /* Vector Table Relocation in Internal FLASH. */
  SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET; 
#endif 
}

/**
 * @brief  Update SystemCoreClock variable according to Clock Register Values.
 *         The SystemCoreClock variable contains the core clock (HCLK), it can
 *         be used by the user application to setup the SysTick timer or configure
 *         other parameters.
 *           
 * @note   Each time the core clock (HCLK) changes, this function must be called
 *         to update SystemCoreClock variable value. Otherwise, any configuration
 *         based on this variable will be incorrect.         
 *     
 * @note   
 *		- The system frequency computed by this function is not the real 
 *        frequency in the chip. It is calculated based on the predefined 
 *        constant and the selected clock source:
 *             
 *		- If SYSCLK source is HSI, SystemCoreClock will contain the HSI_VALUE(*)
 *                                              
 *		- If SYSCLK source is HSE, SystemCoreClock will contain the HSE_VALUE(**)
 *                          
 *		- If SYSCLK source is PLL, SystemCoreClock will contain the HSE_VALUE(**) 
 *             or HSI_VALUE(*) multiplied by the PLL factors.
 *         
 *       (*) HSI_VALUE is a constant defined in stm32f1xx.h file (default value
 *           8 MHz) but the real value may vary depending on the variations
 *           in voltage and temperature.   
 *    
 *       (**) HSE_VALUE is a constant defined in stm32f1xx.h file (default value
 *            8 MHz or 25 MHz, depedning on the product used), user has to ensure
 *            that HSE_VALUE is same as the real frequency of the crystal used.
 *            Otherwise, this function may have wrong result.
 *                
 *		- The result of this function could be not correct when using fractional
 *           value for HSE crystal.
 * @param  None
 * @retval None
 */
void SystemCoreClockUpdate (void)
{
  uint32_t tmp = 0, pllmull = 0, pllsource = 0;

  /* Get SYSCLK source */
  tmp = RCC->CFGR & RCC_CFGR_SWS;
  
  switch (tmp)
  {
    case 0x00:  /* HSI used as system clock */
      SystemCoreClock = HSI_VALUE;
      break;
    case 0x04:  /* HSE used as system clock */
      SystemCoreClock = HSE_VALUE;
      break;
    case 0x08:  /* PLL used as system clock */

      /* Get PLL clock source and multiplication factor */
      pllmull = RCC->CFGR & RCC_CFGR_PLLMULL;
      pllsource = RCC->CFGR & RCC_CFGR_PLLSRC;
      
      pllmull = ( pllmull >> 18) + 2;
      
      if (pllsource == 0x00)
      {
        /* HSI oscillator clock divided by 2 selected as PLL clock entry */
        SystemCoreClock = (HSI_VALUE >> 1) * pllmull;
      }
      else
      {
        /* HSE selected as PLL clock entry */
        if ((RCC->CFGR & RCC_CFGR_PLLXTPRE) != (uint32_t)RESET)
        {/* HSE oscillator clock divided by 2 */
          SystemCoreClock = (HSE_VALUE >> 1) * pllmull;
        }
        else
        {
          SystemCoreClock = HSE_VALUE * pllmull;
        }
      }
      break;

    default:
      SystemCoreClock = HSI_VALUE;
      break;
  }
  
  /* Compute HCLK clock frequency */
  /* Get HCLK prescaler */
  tmp = AHBPrescTable[((RCC->CFGR & RCC_CFGR_HPRE) >> 4)];
  /* HCLK clock frequency */
  SystemCoreClock >>= tmp;  
}

/**
 * @brief  Configures the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers.
 * @param  None
 * @retval None
 */
static void SetSysClock(void)
{
  SetSysClockTo72();
}


/**
 * @brief  Sets System clock frequency to 72MHz and configure HCLK, PCLK2 
 *          and PCLK1 prescalers. 
 * @note   This function should be used only after reset.
 * @param  None
 * @retval None
 */
static void SetSysClockTo72(void)
{
  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
  
  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration */    
  /* Enable HSE */    
  RCC->CR |= ((uint32_t)RCC_CR_HSEON);
 
  /* Wait till HSE is ready and if Time out is reached exit */
  do
  {
    HSEStatus = RCC->CR & RCC_CR_HSERDY;
    StartUpCounter++;  
  } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

  if ((RCC->CR & RCC_CR_HSERDY) != RESET)
  {
    HSEStatus = (uint32_t)0x01;
  }
  else
  {
    HSEStatus = (uint32_t)0x00;
  }  

  if (HSEStatus == (uint32_t)0x01)
  {
    /* Enable Prefetch Buffer */
    FLASH->ACR |= FLASH_ACR_PRFTBE;

    /* Flash 2 wait state */
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;    
 
    /* HCLK = SYSCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
      
    /* PCLK2 = HCLK */
	/*
	 * According to the RM0008 recomendation (p.542), It is recommended to
	 * set PCLK2 to 9MHz when you need SDIO SD card interface, but it is
	 * doubtful.
	 */
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
	/*
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV8;
	 */
    
    /* PCLK1 = HCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;

    /*  PLL configuration: PLLCLK = HSE * 9 = 72 MHz */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE |
                                        RCC_CFGR_PLLMULL));
    RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL9);

    /* Enable PLL */
    RCC->CR |= RCC_CR_PLLON;

    /* Wait till PLL is ready */
    while((RCC->CR & RCC_CR_PLLRDY) == 0)
    {
    }
    
    /* Select PLL as system clock source */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
    RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;    

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08)
    {
    }
  }
  else
  { /* If HSE fails to start-up, the application will have wrong clock 
         configuration. User can add here some code to deal with this error */
  }
}

/* End of File */
