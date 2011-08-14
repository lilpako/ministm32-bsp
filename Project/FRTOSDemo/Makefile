####################################################################
# Makefile                                                         #
####################################################################

.PHONY: all clean xref flash reset

####################################################################
# Definitions                                                      #
####################################################################

PROJECTNAME = FRTOSDemo
OBJ_DIR = build
EXE_DIR = exe
LST_DIR = lst

####################################################################
# Definitions of toolchain.                                        #
# You might need to change paths/etc to match your system          #
# This makefile assumes that the tools are in the users PATH       #
####################################################################

# CodeSourcery G++ Lite

# Uncomment the following lines for Windows environment
# You may have to replace the backslashes with slashes
#TOOLDIR = "C:\Program Files\CodeSourcery\Sourcery G++ Lite"
#GCCVERSION = "4.5.2"
#CC = $(TOOLDIR)\bin\arm-none-eabi-gcc
#LD = $(TOOLDIR)\bin\arm-none-eabi-ld
#AR = $(TOOLDIR)\bin\arm-none-eabi-ar
#OBJCOPY = $(TOOLDIR)\bin\arm-none-eabi-objcopy
#RM = $(TOOLDIR)\bin\cs-rm -rf

# Uncomment the following lines for Linux
# Don't forget to check your CS tool directory
TOOLDIR = ${HOME}/CodeSourcery/arm-2011.03
GCCVERSION = 4.5.2
CC = $(TOOLDIR)/bin/arm-none-eabi-gcc
LD = $(TOOLDIR)/bin/arm-none-eabi-ld
AR = $(TOOLDIR)/bin/arm-none-eabi-ar
OBJCOPY = $(TOOLDIR)/bin/arm-none-eabi-objcopy
RM = rm -rf

####################################################################
# Flags                                                            #
####################################################################

# C Dialect
CFLAGS += -fsigned-char 
# ARM specific
CFLAGS += -mthumb 
CFLAGS += -mcpu=cortex-m3
CFLAGS += -mlittle-endian
# Gdb support
CFLAGS += -g 
# Optimization
CFLAGS += -Os 
CFLAGS += -ffunction-sections 
# preprocessor
CFLAGS += -MD 
# stm32f10x.h
CFLAGS += -D STM32F10X_HD
CFLAGS += -D USE_STDPERIPH_DRIVER 

# ARM specific
ASMFLAGS += -mthumb 
ASMFLAGS += -mcpu=cortex-m3
ASMFLAGS += -mlittle-endian
# Passing options to assembler
ASMFLAGS += -Wa,-EL 

# ARM specific
LDFLAGS += -mthumb 
LDFLAGS += -mcpu=cortex-m3
LDFLAGS += -mlittle-endian
# Passing options to linker
LDFLAGS += -Xlinker 
LDFLAGS += -Map=$(LST_DIR)/$(PROJECTNAME).map 
LDFLAGS += -T./miniSTM32.ld
LDFLAGS += -L$(TOOLDIR)/arm-none-eabi/lib/thumb2
LDFLAGS += -L$(TOOLDIR)/lib/gcc/arm-none-eabi/$(GCCVERSION)/thumb2

LIBS += -lc -lcs3 -lcs3unhosted

INCLUDEPATHS += -I . 
INCLUDEPATHS += -I ../../Libraries/CMSIS/CM3/CoreSupport
INCLUDEPATHS += -I ../../Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x
INCLUDEPATHS += -I ../../Libraries/STM32F10x_StdPeriph_Driver/inc
INCLUDEPATHS += -I ../../Utilities/miniSTM32
INCLUDEPATHS += -I ../../Utilities/Support
INCLUDEPATHS += -I ../../FreeRTOS_Source/include
INCLUDEPATHS += -I ../../FreeRTOS_Source/portable/GCC/ARM_CM3

XREFSPATHS = -s .
XREFSPATHS += -s ../../Libraries
XREFSPATHS += -s ../../Utilities

####################################################################
# Files
####################################################################

C_SRC = ./main.c
# FreeRTOS replace this routine
#C_SRC += ./stm32f10x_it.c
C_SRC += ./system_stm32f10x.c

# CMSIS support
C_SRC += ../../Libraries/CMSIS/CM3/CoreSupport/core_cm3.c

# Pepheral support : choose files you need
C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/misc.c
C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_adc.c
#C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_bkp.c
#C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_can.c
#C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_cec.c
#C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_crc.c
#C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_dac.c
#C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_dbgmcu.c
C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_dma.c
C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_exti.c
#C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_flash.c
#C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_fsmc.c
C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.c
C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_i2c.c
#C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_iwdg.c
#C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_pwr.c
C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.c
#C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_rtc.c
C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_sdio.c
C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_spi.c
C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_tim.c
C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_usart.c
#C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_wwdg.c

# Board support 
C_SRC += ../../Utilities/miniSTM32/miniSTM32.c
C_SRC += ../../Utilities/miniSTM32/miniSTM32_sio.c


# Support functions
C_SRC += ../../Utilities/Support/syscalls.c
C_SRC += ../../Utilities/Support/term_io.c
C_SRC += ../../Utilities/Support/comm.c

# FreeRTOS 
C_SRC += ../../FreeRTOS_Source/list.c
C_SRC += ../../FreeRTOS_Source/queue.c
C_SRC += ../../FreeRTOS_Source/tasks.c
C_SRC += ../../FreeRTOS_Source/timers.c
C_SRC += ../../FreeRTOS_Source/portable/GCC/ARM_CM3/port.c
C_SRC += ../../FreeRTOS_Source/portable/MemMang/heap_1.c

# Startup 
S_SRC = ../../Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/gcc_ride7/startup_stm32f10x_hd.s

####################################################################
# Rules                                                            #
####################################################################

C_FILES = $(notdir $(C_SRC) )
S_FILES = $(notdir $(S_SRC) )
#make list of source paths, sort also removes duplicates
C_PATHS = $(sort $(dir $(C_SRC) ) )
S_PATHS = $(sort $(dir $(S_SRC) ) )

C_OBJS = $(addprefix $(OBJ_DIR)/, $(C_FILES:.c=.o))
S_OBJS = $(addprefix $(OBJ_DIR)/, $(S_FILES:.s=.o))

vpath %.c $(C_PATHS)
vpath %.s $(S_PATHS)

# Default build is debug build
all:      debug

debug:    CFLAGS += -DDEBUG -g3 -O0
debug:    $(OBJ_DIR) $(LST_DIR) $(EXE_DIR)/$(PROJECTNAME).out $(EXE_DIR)/$(PROJECTNAME).bin

release:  CFLAGS += -DNDEBUG -O3 
release:  $(OBJ_DIR) $(LST_DIR) $(EXE_DIR)/$(PROJECTNAME).out $(EXE_DIR)/$(PROJECTNAME).bin

# Create directories
$(OBJ_DIR):
	mkdir $(OBJ_DIR)
	@echo "Created build directory."

$(EXE_DIR):
	mkdir $(EXE_DIR)
	@echo "Created executable directory."

$(LST_DIR):
	mkdir $(LST_DIR)
	@echo "Created list directory."

# Create objects from C SRC files
$(OBJ_DIR)/%.o: %.c $(OBJ_DIR)
	@echo "Building file: $<"
	$(CC) $(CFLAGS) $(INCLUDEPATHS) -c -o $@ $<

# Assemble .s files
$(OBJ_DIR)/%.o: %.s $(OBJ_DIR)
	@echo "Assembling $<"
	$(CC) $(ASMFLAGS) $(INCLUDEPATHS) -c -o $@ $<

# Link
$(EXE_DIR)/$(PROJECTNAME).out: $(OBJ_DIR) $(EXE_DIR) $(LST_DIR) $(C_OBJS) $(S_OBJS)
	@echo "Linking target: $@"
	$(CC) $(LDFLAGS) $(C_OBJS) $(S_OBJS) $(LIBS) -o $(EXE_DIR)/$(PROJECTNAME).out

# Create binary file
$(EXE_DIR)/$(PROJECTNAME).bin: $(EXE_DIR)/$(PROJECTNAME).out
	@echo "Creating binary file"
	$(OBJCOPY) -O binary $(EXE_DIR)/$(PROJECTNAME).out $(EXE_DIR)/$(PROJECTNAME).bin

clean: 
	$(RM) $(OBJ_DIR) $(LST_DIR) $(EXE_DIR)
	$(RM) cscope.out

# Create cross-reference file for cscope
xref:
	cscope -R -b $(INCLUDEPATHS) $(XREFSPATHS)

# Flash download via openocd
flash:
	openocd -f stm32flash.cfg

# Reset via openocd
reset:
	openocd -f stm32reset.cfg

# End of File #
