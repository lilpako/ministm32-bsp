/*******************************************************************************
 * @file	Project/LCDDemo/miniSTM32.ld
 * @author	Brian
 * @version	V0.1.0
 * @date	07-August-2011
 * @brief	Linker script for CodeSourcery 2011
 */

GROUP(
"libc.a"
"libm.a"
)

/* stack control */

__Stack_Size = 1024 ;

PROVIDE ( _Stack_Size = __Stack_Size ) ;

__Stack_Init = _estack  - __Stack_Size ;

PROVIDE ( _Stack_Init = __Stack_Init ) ;

_Minimum_Stack_Size = 0x100 ;


/* this sends all unreferenced IRQHandlers to reset */

PROVIDE (   Undefined_Handler = 0 ) ;
PROVIDE (   SWI_Handler = 0 ) ;
PROVIDE (   IRQ_Handler = 0 ) ;
PROVIDE (   Prefetch_Handler = 0 ) ;
PROVIDE (   Abort_Handler = 0 ) ;
PROVIDE (   FIQ_Handler = 0 ) ;

PROVIDE (   NMIException = 0 ) ;
PROVIDE (   NMI_Handler = 0 ) ;
PROVIDE (   HardFaultException = 0 ) ;
PROVIDE (   HardFault_Handler = 0 ) ;
PROVIDE (   MemManageException = 0 ) ;
PROVIDE (   MemManage_Handler = 0 ) ;
PROVIDE (   BusFaultException = 0 ) ;
PROVIDE (   BusFault_Handler = 0 ) ;
PROVIDE (   UsageFaultException = 0 ) ;
PROVIDE (   UsageFault_Handler = 0 ) ;

PROVIDE (   SVCHandler = 0 ) ;
PROVIDE (   SVC_Handler = 0 ) ;
PROVIDE (   DebugMonitor = 0 ) ;
PROVIDE (   DebugMon_Handler = 0 ) ;
PROVIDE (   PendSVC = 0 ) ;
PROVIDE (   PendSV_Handler = 0 ) ;
PROVIDE (   SysTickHandler = 0 ) ;
PROVIDE (   SysTick_Handler = 0 ) ;

PROVIDE (   WWDG_IRQHandler = 0 ) ;
PROVIDE (   PVD_IRQHandler = 0 ) ;
PROVIDE (   TAMPER_IRQHandler = 0 ) ;
PROVIDE (   RTC_IRQHandler = 0 ) ;
PROVIDE (   FLASH_IRQHandler = 0 ) ;
PROVIDE (   RCC_IRQHandler = 0 ) ;
PROVIDE (   EXTI0_IRQHandler = 0 ) ;
PROVIDE (   EXTI1_IRQHandler = 0 ) ;
PROVIDE (   EXTI2_IRQHandler = 0 ) ;
PROVIDE (   EXTI3_IRQHandler = 0 ) ;
PROVIDE (   EXTI4_IRQHandler = 0 ) ;
PROVIDE (   DMAChannel1_IRQHandler = 0 ) ;
PROVIDE (   DMAChannel2_IRQHandler = 0 ) ;
PROVIDE (   DMAChannel3_IRQHandler = 0 ) ;
PROVIDE (   DMAChannel4_IRQHandler = 0 ) ;
PROVIDE (   DMAChannel5_IRQHandler = 0 ) ;
PROVIDE (   DMAChannel6_IRQHandler = 0 ) ;
PROVIDE (   DMAChannel7_IRQHandler = 0 ) ;
PROVIDE (   DMA1_Channel1_IRQHandler = 0 ) ;
PROVIDE (   DMA1_Channel2_IRQHandler = 0 ) ;
PROVIDE (   DMA1_Channel3_IRQHandler = 0 ) ;
PROVIDE (   DMA1_Channel4_IRQHandler = 0 ) ;
PROVIDE (   DMA1_Channel5_IRQHandler = 0 ) ;
PROVIDE (   DMA1_Channel6_IRQHandler = 0 ) ;
PROVIDE (   DMA1_Channel7_IRQHandler = 0 ) ;
PROVIDE (   ADC_IRQHandler = 0 ) ;
PROVIDE (   ADC1_2_IRQHandler = 0 ) ;
PROVIDE (   USB_HP_CAN_TX_IRQHandler = 0 ) ;
PROVIDE (   USB_HP_CAN1_TX_IRQHandler = 0 ) ;
PROVIDE (   USB_LP_CAN_RX0_IRQHandler = 0 ) ;
PROVIDE (   USB_LP_CAN1_RX0_IRQHandler = 0 ) ;
PROVIDE (   CAN_RX1_IRQHandler = 0 ) ;
PROVIDE (   CAN1_RX1_IRQHandler = 0 ) ;
PROVIDE (   CAN_SCE_IRQHandler = 0 ) ;
PROVIDE (   CAN1_SCE_IRQHandler = 0 ) ;
PROVIDE (   EXTI9_5_IRQHandler = 0 ) ;
PROVIDE (   TIM1_BRK_IRQHandler = 0 ) ;
PROVIDE (   TIM1_UP_IRQHandler = 0 ) ;
PROVIDE (   TIM1_TRG_COM_IRQHandler = 0 ) ;
PROVIDE (   TIM1_CC_IRQHandler = 0 ) ;
PROVIDE (   TIM2_IRQHandler = 0 ) ;
PROVIDE (   TIM3_IRQHandler = 0 ) ;
PROVIDE (   TIM4_IRQHandler = 0 ) ;
PROVIDE (   I2C1_EV_IRQHandler = 0 ) ;
PROVIDE (   I2C1_ER_IRQHandler = 0 ) ;
PROVIDE (   I2C2_EV_IRQHandler = 0 ) ;
PROVIDE (   I2C2_ER_IRQHandler = 0 ) ;
PROVIDE (   SPI1_IRQHandler = 0 ) ;
PROVIDE (   SPI2_IRQHandler = 0 ) ;
PROVIDE (   USART1_IRQHandler = 0 ) ;
PROVIDE (   USART2_IRQHandler = 0 ) ;
PROVIDE (   USART3_IRQHandler = 0 ) ;
PROVIDE (   EXTI15_10_IRQHandler = 0 ) ;
PROVIDE (   RTCAlarm_IRQHandler = 0 ) ;
PROVIDE (   USBWakeUp_IRQHandler = 0 ) ;
PROVIDE (   TIM8_BRK_IRQHandler = 0 ) ;
PROVIDE (   TIM8_UP_IRQHandler = 0 );
PROVIDE (   TIM8_TRG_COM_IRQHandler = 0 ) ;
PROVIDE (   TIM8_CC_IRQHandler = 0 ) ;
PROVIDE (   ADC3_IRQHandler = 0 ) ;
PROVIDE (   FSMC_IRQHandler = 0 ) ;
PROVIDE (   SDIO_IRQHandler = 0 ) ;
PROVIDE (   TIM5_IRQHandler = 0 ) ;
PROVIDE (   SPI3_IRQHandler = 0 ) ;
PROVIDE (   UART4_IRQHandler = 0 ) ;
PROVIDE (   UART5_IRQHandler = 0 ) ;
PROVIDE (   TIM6_IRQHandler = 0 ) ;
PROVIDE (   TIM7_IRQHandler = 0 ) ;
PROVIDE (   DMA2_Channel1_IRQHandler = 0 ) ;
PROVIDE (   DMA2_Channel2_IRQHandler = 0 ) ;
PROVIDE (   DMA2_Channel3_IRQHandler = 0 ) ;
PROVIDE (   DMA2_Channel4_5_IRQHandler = 0 ) ;

/* Peripheral and SRAM base address in the alias region */

PERIPH_BB_BASE        = 0x42000000;
SRAM_BB_BASE          = 0x22000000;

/* Peripheral and SRAM base address in the bit-band region */

SRAM_BASE             = 0x20000000;
PERIPH_BASE           = 0x40000000;

/* Flash registers base address */

PROVIDE ( FLASH_BASE            = 0x40022000);

/* Flash Option Bytes base address */

PROVIDE ( OB_BASE               = 0x1FFFF800);

/* Peripheral memory map */

APB1PERIPH_BASE      = PERIPH_BASE  ;
APB2PERIPH_BASE      = (PERIPH_BASE + 0x10000) ;
AHBPERIPH_BASE       = (PERIPH_BASE + 0x20000) ;

PROVIDE ( TIM2            = (APB1PERIPH_BASE + 0x0000) ) ;
PROVIDE ( TIM3            = (APB1PERIPH_BASE + 0x0400) ) ;
PROVIDE ( TIM4            = (APB1PERIPH_BASE + 0x0800) ) ;
PROVIDE ( RTC             = (APB1PERIPH_BASE + 0x2800) ) ;
PROVIDE ( WWDG            = (APB1PERIPH_BASE + 0x2C00) ) ;
PROVIDE ( IWDG            = (APB1PERIPH_BASE + 0x3000) ) ;
PROVIDE ( SPI2            = (APB1PERIPH_BASE + 0x3800) ) ;
PROVIDE ( USART2          = (APB1PERIPH_BASE + 0x4400) ) ;
PROVIDE ( USART3          = (APB1PERIPH_BASE + 0x4800) ) ;
PROVIDE ( I2C1            = (APB1PERIPH_BASE + 0x5400) ) ;
PROVIDE ( I2C2            = (APB1PERIPH_BASE + 0x5800) ) ;
PROVIDE ( CAN             = (APB1PERIPH_BASE + 0x6400) ) ;
PROVIDE ( BKP             = (APB1PERIPH_BASE + 0x6C00) ) ;
PROVIDE ( PWR             = (APB1PERIPH_BASE + 0x7000) ) ;

PROVIDE ( AFIO            = (APB2PERIPH_BASE + 0x0000) ) ;
PROVIDE ( EXTI            = (APB2PERIPH_BASE + 0x0400) ) ;
PROVIDE ( GPIOA           = (APB2PERIPH_BASE + 0x0800) ) ;
PROVIDE ( GPIOB           = (APB2PERIPH_BASE + 0x0C00) ) ;
PROVIDE ( GPIOC           = (APB2PERIPH_BASE + 0x1000) ) ;
PROVIDE ( GPIOD           = (APB2PERIPH_BASE + 0x1400) ) ;
PROVIDE ( GPIOE           = (APB2PERIPH_BASE + 0x1800) ) ;
PROVIDE ( ADC1            = (APB2PERIPH_BASE + 0x2400) ) ;
PROVIDE ( ADC2            = (APB2PERIPH_BASE + 0x2800) ) ;
PROVIDE ( TIM1            = (APB2PERIPH_BASE + 0x2C00) ) ;
PROVIDE ( SPI1            = (APB2PERIPH_BASE + 0x3000) ) ;
PROVIDE ( USART1          = (APB2PERIPH_BASE + 0x3800) ) ;

PROVIDE ( DMA             = (AHBPERIPH_BASE + 0x0000) ) ;
PROVIDE ( DMA_Channel1    = (AHBPERIPH_BASE + 0x0008) ) ;
PROVIDE ( DMA_Channel2    = (AHBPERIPH_BASE + 0x001C) ) ;
PROVIDE ( DMA_Channel3    = (AHBPERIPH_BASE + 0x0030) ) ;
PROVIDE ( DMA_Channel4    = (AHBPERIPH_BASE + 0x0044) ) ;
PROVIDE ( DMA_Channel5    = (AHBPERIPH_BASE + 0x0058) ) ;
PROVIDE ( DMA_Channel6    = (AHBPERIPH_BASE + 0x006C) ) ;
PROVIDE ( DMA_Channel7    = (AHBPERIPH_BASE + 0x0080) ) ;
PROVIDE ( RCC             = (AHBPERIPH_BASE + 0x1000) ) ;

/* System Control Space memory map */

SCS_BASE              = 0xE000E000;

PROVIDE ( SysTick         = (SCS_BASE + 0x0010) ) ;
PROVIDE ( NVIC            = (SCS_BASE + 0x0100) ) ;
PROVIDE ( SCB             = (SCS_BASE + 0x0D00) ) ;


/* Reset entry point */

ENTRY(Reset_Handler)

/* Memory Spaces Definitions */

MEMORY
{
  RAM        (RWX) : ORIGIN = 0x20000000, LENGTH = 0x10000 /* 64KB */
  FLASH      (RX)  : ORIGIN = 0x08000000, LENGTH = 0x80000 /* 512KB */
}

/* higher address of the user mode stack */

_estack = ORIGIN(RAM) + LENGTH(RAM);


/* Sections Definitions */

SECTIONS
{
    /* code section */
    .text :
    {
	    . = ALIGN(0x80);
		_isr_vectors_offs = . - 0x08000000;
        KEEP(*(.isr_vector)) 
		. = ALIGN(4);
		CREATE_OBJECT_SYMBOLS
        *(.text)            
        *(.text.*)         
		*(.gnu.linkonce.t.*)
		*(.plt)
		*(.gnu.warning)
		*(.glue_7t)
		*(.glue_7)
		*(.vfp11_veneer)
		*(.ARM.extab* .gnu.linkonce.armextab.*)
		*(.gcc_execpt_table)
	} >FLASH

	.eh_frame_hdr : ALIGN (4)
	{
		KEEP (*(.eh_frame_hdr))
	} >FLASH

	PROVIDE_HIDDEN (__exidx_start = .);
	.ARM.exidx :
	{
		*(.ARM.exidx* .gnu.linkonce.armexidx.*)
	} >FLASH
	PROVIDE_HIDDEN (__exidx_end = .);

	/* read-only data section */
	.rodata : ALIGN (4)
	{
        *(.rodata)
        *(.rodata*)
		*(.gnu.linkonce.r.*)

	    . = ALIGN(4);
		KEEP(*(.init))

		. = ALIGN(4);
		__preinit_array_start = .;
		KEEP(*(.preinit_arrary))
		__preinit_array_end = .;

		. = ALIGN(4);
		__init_array_start = .;
		KEEP (*(SORT(.init_array.*)))
		KEEP (*(.init_array))
		__init_array_end = .;
 
		. = ALIGN(4);
		KEEP(*(.fini))
 
		. = ALIGN(4);
		__fini_array_start = .;
		KEEP (*(.fini_array))
		KEEP (*(SORT(.fini_array.*)))
		__fini_array_end = .;
 
		*(.init .init.*)
		*(.fini .fini.*)
 
		PROVIDE_HIDDEN (__preinit_array_start = .);
		KEEP (*(.preinit_array))
		PROVIDE_HIDDEN (__preinit_array_end = .);
		PROVIDE_HIDDEN (__init_array_start = .);
		KEEP (*(SORT(.init_array.*)))
		KEEP (*(.init_array))
		PROVIDE_HIDDEN (__init_array_end = .);
		PROVIDE_HIDDEN (__fini_array_start = .);
		KEEP (*(.fini_array))
		KEEP (*(SORT(.fini_array.*)))
		PROVIDE_HIDDEN (__fini_array_end = .);

		. = ALIGN (8);
		*(.rom)
		*(.rom.b)

		_etext = .;
		_sidata = _etext;

	} >FLASH
 
    /* initialized data section */
    .data  : AT ( _sidata )
    {
	    . = ALIGN(4);
        _sdata = . ;
        _data = . ;
        
		KEEP(*(.jcr))
		*(.got.plt)
		*(.got)
		*(.shdata)
        *(.data)
        *(.data.*)
		*(.gnu.linkonce.d.*)
        *(.RAMtext)

		. = ALIGN(8);
		*(.ram)
		*(.ramfunc*);

	    . = ALIGN(4);
   	 _edata = . ;
    } >RAM
    
    /* calculate end address of idata */
    _eidata = _sidata + _edata - _sdata ;
    
    /* check that idata remains in FLASH region */
    _lastdataromaddress = ORIGIN(FLASH) + LENGTH(FLASH);
    toobig = ( _eidata > _lastdataromaddress) ? "!!!!!!!!! FLASH IS FULL !!!!!!!!!" : 0 ;

    /* uninitialized data section */
    .bss :
    {
	    . = ALIGN(4);
        _sbss = .;
        _bss = .;
        
        *(.bss)
		*(.bss.*)
        *(COMMON)

		. = ALIGN(8);
		*(.ram.b)
        
	    . = ALIGN(4);
   	 	_ebss = . ;
    } >RAM
    
    PROVIDE ( end = _ebss );
    PROVIDE ( _end = _ebss );
    
    /* user stack section   */
    ._usrstack :
    {
	    . = ALIGN(4);
        _susrstack = . ;
        
        . = . + _Minimum_Stack_Size ;
        
	    . = ALIGN(4);
        _eusrstack = . ;
    } >RAM
    
    /* remove the debugging information from the standard libraries */
    /DISCARD/ :
	{
	libc.a ( * )
	libm.a ( * )
	libgcc.a ( * )
	}

    /* Stabs debugging sections.  */
    .stab          0 : { *(.stab) }
    .stabstr       0 : { *(.stabstr) }
    .stab.excl     0 : { *(.stab.excl) }
    .stab.exclstr  0 : { *(.stab.exclstr) }
    .stab.index    0 : { *(.stab.index) }
    .stab.indexstr 0 : { *(.stab.indexstr) }
    .comment       0 : { *(.comment) }
    /* DWARF 1 */
    .debug          0 : { *(.debug) }
    .line           0 : { *(.line) }
    /* GNU DWARF 1 extensions */
    .debug_srcinfo  0 : { *(.debug_srcinfo) }
    .debug_sfnames  0 : { *(.debug_sfnames) }
    /* DWARF 1.1 and DWARF 2 */
    .debug_aranges  0 : { *(.debug_aranges) }
    .debug_pubnames 0 : { *(.debug_pubnames) }
    /* DWARF 2 */
    .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
    .debug_abbrev   0 : { *(.debug_abbrev) }
    .debug_line     0 : { *(.debug_line) }
    .debug_frame    0 : { *(.debug_frame) }
    .debug_str      0 : { *(.debug_str) }
    .debug_loc      0 : { *(.debug_loc) }
    .debug_macinfo  0 : { *(.debug_macinfo) }
    /* SGI/MIPS DWARF 2 extensions */
    .debug_weaknames 0 : { *(.debug_weaknames) }
    .debug_funcnames 0 : { *(.debug_funcnames) }
    .debug_typenames 0 : { *(.debug_typenames) }
    .debug_varnames  0 : { *(.debug_varnames) }

	.note.gnu.arm.ident 0 : { KEEP (*(.note.gnu.arm.ident)) }
	.ARM.attributes  0 : { KEEP (*(.ARM.attributes)) }
	/DISCARD/ : { *(.note.GNU-stack) }
}

/* End of File */
