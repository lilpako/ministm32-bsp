####################################################################
# PHONY definitions                                                #
####################################################################

.PHONY: all clean xref flash reset gdb

####################################################################
# Definitions                                                      #
####################################################################

PROJECTNAME = FontDemo
OBJ_DIR = build
EXE_DIR = exe
LST_DIR = lst
SCRIPTDIR = ../../Utilities/Script
#JTAGDEV = flyswatter
JTAGDEV = luminary-icdi

####################################################################
# Tool Chain Definitions                                           #
#																   #
# You might need to change paths/etc to match your system.         #
# On Windows, it also depends on the make utility you are using.   #
# The following definitins are tested with GnuWin32 make v3.8.1.   #
####################################################################

# CodeSourcery G++ Lite Tool setting

# Windows
ifdef SystemRoot

TOOLDIR = "C:\Program Files\CodeSourcery\Sourcery G++ Lite"
GCCVERSION = "4.5.2"
CC = $(TOOLDIR)\bin\arm-none-eabi-gcc
LD = $(TOOLDIR)\bin\arm-none-eabi-ld
AR = $(TOOLDIR)\bin\arm-none-eabi-ar
GDB = $(TOOLDIR)\bin\arm-none-eabi-gdb
OBJCOPY = $(TOOLDIR)\bin\arm-none-eabi-objcopy
RM = $(TOOLDIR)\bin\cs-rm -rf

# Linux
else

TOOLDIR = ${HOME}/CodeSourcery/arm-2011.03
GCCVERSION = 4.5.2
CC = $(TOOLDIR)/bin/arm-none-eabi-gcc
LD = $(TOOLDIR)/bin/arm-none-eabi-ld
AR = $(TOOLDIR)/bin/arm-none-eabi-ar
GDB = $(TOOLDIR)/bin/arm-none-eabi-gdb
OBJCOPY = $(TOOLDIR)/bin/arm-none-eabi-objcopy
RM = rm -rf

endif

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

# preprocessor
CFLAGS += -MD 

# stm32f10x.h specific
CFLAGS += -D STM32F10X_HD
CFLAGS += -D USE_STDPERIPH_DRIVER 

# garbage collection: this doesn't seem to work with CSLite
CFLAGS += -ffunction-sections 
CFLAGS += -Wl,--gc-sections

# hardware specific definitions
#CFLAGS += -D LCD_QD024CPS25
#CFLAGS += -D LCD_HSD043I9W
CFLAGS += -D LCD_AT043TN13
#CFLAGS += -D LCD_AT070TN83

# enable LCD test pattern drawing functions
#CFLAGS += -D LCD_TEST

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
LDFLAGS += -T$(SCRIPTDIR)/Linker/miniSTM32.ld
LDFLAGS += -L$(TOOLDIR)/arm-none-eabi/lib/thumb2
LDFLAGS += -L$(TOOLDIR)/lib/gcc/arm-none-eabi/$(GCCVERSION)/thumb2

LIBS += -lc -lcs3 -lcs3unhosted

INCLUDEPATHS += -I . 
INCLUDEPATHS += -I ../../Libraries/CMSIS/CM3/CoreSupport
INCLUDEPATHS += -I ../../Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x
INCLUDEPATHS += -I ../../Libraries/STM32F10x_StdPeriph_Driver/inc
INCLUDEPATHS += -I ../../Utilities/miniSTM32
INCLUDEPATHS += -I ../../Utilities/FatFs
INCLUDEPATHS += -I ../../Utilities/Fonts
INCLUDEPATHS += -I ../../Utilities/Support

# CSCOPE search path
XREFSPATHS = -s .
XREFSPATHS += -s ../../Libraries
XREFSPATHS += -s ../../Utilities

####################################################################
# Files                                                            #
####################################################################

C_SRC = ./main.c
C_SRC += ./stm32f10x_it.c
C_SRC += ./system_stm32f10x.c

# CMSIS support
C_SRC += ../../Libraries/CMSIS/CM3/CoreSupport/core_cm3.c

# Pepheral support
C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/misc.c
#C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_adc.c
#C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_bkp.c
#C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_can.c
#C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_cec.c
#C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_crc.c
#C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_dac.c
#C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_dbgmcu.c
C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_dma.c
C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_exti.c
#C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_flash.c
C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_fsmc.c
C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.c
C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_i2c.c
#C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_iwdg.c
#C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_pwr.c
C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.c
C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_rtc.c
C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_sdio.c
C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_spi.c
C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_tim.c
C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_usart.c
#C_SRC += ../../Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_wwdg.c

# Board support 
C_SRC += ../../Utilities/miniSTM32/miniSTM32.c
#C_SRC += ../../Utilities/miniSTM32/miniSTM32_sdc.c
#C_SRC += ../../Utilities/miniSTM32/miniSTM32_diskio.c
#C_SRC += ../../Utilities/miniSTM32/miniSTM32_flash.c
C_SRC += ../../Utilities/miniSTM32/miniSTM32_lcd.c
#C_SRC += ../../Utilities/miniSTM32/miniSTM32_tsc.c
#C_SRC += ../../Utilities/miniSTM32/miniSTM32_sio.c

# Support functions : NewLibrary
C_SRC += ../../Utilities/Support/syscalls.c
C_SRC += ../../Utilities/Support/term_io.c
C_SRC += ../../Utilities/Support/comm.c

# Support functions : FAT
#C_SRC += ../../Utilities/FatFs/ff.c

# Support functions : Fonts
C_SRC += ../../Utilities/Fonts/DroidSans_10.c
C_SRC += ../../Utilities/Fonts/DroidSans_12.c
C_SRC += ../../Utilities/Fonts/DroidSans_14.c
C_SRC += ../../Utilities/Fonts/DroidSans_16.c
C_SRC += ../../Utilities/Fonts/DroidSans_18.c
C_SRC += ../../Utilities/Fonts/DroidSans_20.c
#C_SRC += ../../Utilities/Fonts/DroidSans_Bold_10.c
#C_SRC += ../../Utilities/Fonts/DroidSans_Bold_12.c
#C_SRC += ../../Utilities/Fonts/DroidSans_Bold_14.c
#C_SRC += ../../Utilities/Fonts/DroidSans_Bold_16.c
C_SRC += ../../Utilities/Fonts/DroidSans_Bold_18.c
#C_SRC += ../../Utilities/Fonts/DroidSans_Bold_20.c
#C_SRC += ../../Utilities/Fonts/DroidSerif_10.c
#C_SRC += ../../Utilities/Fonts/DroidSerif_12.c
#C_SRC += ../../Utilities/Fonts/DroidSerif_14.c
#C_SRC += ../../Utilities/Fonts/DroidSerif_16.c
C_SRC += ../../Utilities/Fonts/DroidSerif_18.c
#C_SRC += ../../Utilities/Fonts/DroidSerif_20.c
#C_SRC += ../../Utilities/Fonts/DroidSerif_Bold_10.c
#C_SRC += ../../Utilities/Fonts/DroidSerif_Bold_12.c
#C_SRC += ../../Utilities/Fonts/DroidSerif_Bold_14.c
#C_SRC += ../../Utilities/Fonts/DroidSerif_Bold_16.c
C_SRC += ../../Utilities/Fonts/DroidSerif_Bold_18.c
#C_SRC += ../../Utilities/Fonts/DroidSerif_Bold_20.c
#C_SRC += ../../Utilities/Fonts/DroidSerif_Italic_10.c
#C_SRC += ../../Utilities/Fonts/DroidSerif_Italic_12.c
#C_SRC += ../../Utilities/Fonts/DroidSerif_Italic_14.c
#C_SRC += ../../Utilities/Fonts/DroidSerif_Italic_16.c
C_SRC += ../../Utilities/Fonts/DroidSerif_Italic_18.c
#C_SRC += ../../Utilities/Fonts/DroidSerif_Italic_20.c
#C_SRC += ../../Utilities/Fonts/Federant_10.c
#C_SRC += ../../Utilities/Fonts/Federant_12.c
#C_SRC += ../../Utilities/Fonts/Federant_14.c
#C_SRC += ../../Utilities/Fonts/Federant_16.c
C_SRC += ../../Utilities/Fonts/Federant_18.c
#C_SRC += ../../Utilities/Fonts/Federant_20.c
#C_SRC += ../../Utilities/Fonts/LiberationSans_10.c
#C_SRC += ../../Utilities/Fonts/LiberationSans_12.c
#C_SRC += ../../Utilities/Fonts/LiberationSans_14.c
#C_SRC += ../../Utilities/Fonts/LiberationSans_16.c
C_SRC += ../../Utilities/Fonts/LiberationSans_18.c
#C_SRC += ../../Utilities/Fonts/LiberationSans_20.c
#C_SRC += ../../Utilities/Fonts/LiberationSerif_10.c
#C_SRC += ../../Utilities/Fonts/LiberationSerif_12.c
#C_SRC += ../../Utilities/Fonts/LiberationSerif_14.c
#C_SRC += ../../Utilities/Fonts/LiberationSerif_16.c
C_SRC += ../../Utilities/Fonts/LiberationSerif_18.c
#C_SRC += ../../Utilities/Fonts/LiberationSerif_20.c
#C_SRC += ../../Utilities/Fonts/LiberationSerif_Italic_10.c
#C_SRC += ../../Utilities/Fonts/LiberationSerif_Italic_12.c
#C_SRC += ../../Utilities/Fonts/LiberationSerif_Italic_14.c
#C_SRC += ../../Utilities/Fonts/LiberationSerif_Italic_16.c
C_SRC += ../../Utilities/Fonts/LiberationSerif_Italic_18.c
#C_SRC += ../../Utilities/Fonts/LiberationSerif_Italic_20.c
#C_SRC += ../../Utilities/Fonts/Ubuntu_10.c
#C_SRC += ../../Utilities/Fonts/Ubuntu_12.c
#C_SRC += ../../Utilities/Fonts/Ubuntu_14.c
#C_SRC += ../../Utilities/Fonts/Ubuntu_16.c
C_SRC += ../../Utilities/Fonts/Ubuntu_18.c
#C_SRC += ../../Utilities/Fonts/Ubuntu_20.c
#C_SRC += ../../Utilities/Fonts/Ubuntu_Bold_10.c
#C_SRC += ../../Utilities/Fonts/Ubuntu_Bold_12.c
#C_SRC += ../../Utilities/Fonts/Ubuntu_Bold_14.c
#C_SRC += ../../Utilities/Fonts/Ubuntu_Bold_16.c
C_SRC += ../../Utilities/Fonts/Ubuntu_Bold_18.c
#C_SRC += ../../Utilities/Fonts/Ubuntu_Bold_20.c
#C_SRC += ../../Utilities/Fonts/Ubuntu_Italic_10.c
#C_SRC += ../../Utilities/Fonts/Ubuntu_Italic_12.c
#C_SRC += ../../Utilities/Fonts/Ubuntu_Italic_14.c
#C_SRC += ../../Utilities/Fonts/Ubuntu_Italic_16.c
C_SRC += ../../Utilities/Fonts/Ubuntu_Italic_18.c
#C_SRC += ../../Utilities/Fonts/Ubuntu_Italic_20.c

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
debug:    $(OBJ_DIR) $(LST_DIR) $(EXE_DIR)/$(PROJECTNAME).out $(EXE_DIR)/flash.bin

release:  CFLAGS += -DNDEBUG -O3 
release:  $(OBJ_DIR) $(LST_DIR) $(EXE_DIR)/$(PROJECTNAME).out $(EXE_DIR)/flash.bin

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
$(EXE_DIR)/flash.bin: $(EXE_DIR)/$(PROJECTNAME).out
	@echo "Creating binary file"
	$(OBJCOPY) -O binary $(EXE_DIR)/$(PROJECTNAME).out $(EXE_DIR)/flash.bin

clean: 
	$(RM) $(OBJ_DIR) $(LST_DIR) $(EXE_DIR)
	$(RM) cscope.out
	$(RM) Session.vim

# Create cross-reference file for cscope
xref:
	cscope -R -b $(INCLUDEPATHS) $(XREFSPATHS)

# Flash download via openocd
flash: 
	openocd -s $(SCRIPTDIR)/OpenOCD -f $(JTAGDEV).cfg -f stm32flash.cfg

# Reset via openocd
reset:
	openocd -s $(SCRIPTDIR)/OpenOCD -f $(JTAGDEV).cfg -f stm32reset.cfg

# Start debug 
# Be sure to execute "monitor shutdown" before exit gdb

ifdef SystemRoot

gdb:
	start "openocd"	openocd -s $(SCRIPTDIR)/OpenOCD -f $(JTAGDEV).cfg -f stm32debug.cfg 
	$(GDB) $(EXE_DIR)/$(PROJECTNAME).out -command=$(SCRIPTDIR)/gdb/gdb.startup

else

gdb:
	xterm -e openocd -s $(SCRIPTDIR)/OpenOCD -f $(JTAGDEV).cfg -f stm32debug.cfg &
	$(GDB) $(EXE_DIR)/$(PROJECTNAME).out -command=$(SCRIPTDIR)/gdb/gdb.startup

endif


# End of File #
