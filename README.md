### STM32 CMake Template

##### Hot to build the template

~~~
git clone https://github.com/matthewphilyaw/stm32_template
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=STM32.cmake ..
~~~

This template uses CMake and is based around the STM32 Cube FW folder that each family comes with (family being L0, F0, F3 etc).

The STM32 Cube FW comes with a Drivers folder, which is assumed to be copied to the root of this template. This template is setup for the L0 range and as such has the Drivers folder from the [STM32Cube_FW_L0_V1.9.0](http://www.st.com/content/st_com/en/products/embedded-software/mcus-embedded-software/stm32-embedded-software/stm32cube-embedded-software/stm32cubel0.html) (Note the actual version at this may change overtime). 

STM32_Settings.cmake contains a setup of variables that configures CMake for the part. Below is the STM32_Settings.cmake that comes with the template. It's steup for the STM32L0xx family, and in particular the [STM32l053xx](http://www.st.com/en/microcontrollers/stm32l053r8.html) which is on the [nucleo-l053r8](http://www.st.com/en/evaluation-tools/nucleo-l053r8.html)

~~~
# MCU PARAMETERS START

# The family the part is from, this is used in various places in the directory structure
set(MCU_FAMILY STM32L0xx)

# The actual part in use
set(MCU_PART STM32L053xx)

# The cortext M series in use, in this case cortex-m0plus
# This will change depending on the series, for exampel cortex m0 is cortext-m0Plus
# This drives the MCPU flag on gcc
set(MCU_MCPU cortex-m0plus)

# While in this template the linkerscript is in the source directory
# This part is very specific to the chip being used
# Typcially in the STM32 Cube FW folder for the a nucleo board for example
# there is a template folder within the boards sub directory for GCC
# and it contains the linker script for that chip. 
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/linker/linkerscript.ld)

# MCU PARAMETERS END

# TOOL CHAIN SETUP START

# The path to the ARM tool chain - this will be different for each
# installtion. This was written on a mac, and happens to be where it 
# was installed
set(TOOL_PATH /usr/local/gcc-arm-none-eabi-5_2-2015q4/bin)

# TOOL CHAIN SETUP END
~~~

This template should be able to easily adapt to other boards in hte L0 family, and has been used with other series as well. Check out the CMakeList.txt, STM32.cmake, STM32_Settings.cmake for more details.
