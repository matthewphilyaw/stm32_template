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
