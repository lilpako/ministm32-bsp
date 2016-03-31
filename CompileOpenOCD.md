# Introduction #

Compiling openocd for windows is straightforward. You can find detailed instruction here (http://dangerousprototypes.com/docs/Compile_OpenOCD_for_Windows). Only difference is that we use cygwin mingw32 compiler.


# Preparation #

## Cygwin ##
Install cygwin. On top of default setting, you need following two packages from Develop category
  * mingw-gcc-core
  * make
After install, login by firing cygwin icon, then create directories for openocd source and FTDI driver, e.g.,
  * /home/user/openocd-0.4.0
  * /home/user/ftd2xx

## OpenOCD source ##
Download openocd source here (http://sourceforge.net/projects/openocd/). You don't have to bother with source from git repository, which requires you to run bootstrap to create configure file. Extract the source into the above directory (/home/user/openocd-0.4.0)

## FTDI driver ##
Find the recent FTDI D2XX driver here(http://www.ftdichip.com/Drivers/D2XX.htm). Extract the driver into the directory /home/user/ftd2xx

# Compiling and Running #
In the openocd source directory, execute

  * ./configure --enable-maintainer-mode --host=i686-pc-mingw32 --disable-werror --with-ftd2xx-win32-zipdir="/home/user/ftd2xx" --with-ftd2xx-lib=static --enable-ft2232\_ftd2xx --disable-at91rm9200
  * make
  * make install

You can find openocd.exe under src directory. Since it is compiled with static option, you don't need any library to run it. Only files you may need are openocd.exe and configuration files under tcl directory. For example, if you use flyswatter to  flash/debug stm32 board, you may need
  * tcl/interface/flyswatter.cfg
  * tcl/target/stm32.cfg
In most cases, there should be no problem in executing openocd with these configuration files, i.e.,
  * openocd -f flyswatter.cfg -f stm32.cfg