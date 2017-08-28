cmake_minimum_required(VERSION 3.8)
enable_language(C ASM)

# Some variable are define in STM32_Settings.cmake

project(stm32_template)

# Project Variables

# In some cases the lower caes versions of these are needed
string(TOLOWER ${MCU_FAMILY} MCU_FAMILY_LOWER)
string(TOLOWER ${MCU_PART} MCU_PART_LOWER)

set(DRIVER_DIR Drivers)

# Definitions

# USE_FULL_LL_DRIVER is used for the LL API from STM
# If not in use the define can be removed below

add_definitions(-D${MCU_PART} -DUSE_FULL_LL_DRIVER)

# Includes
include_directories(
        include
        ${DRIVER_DIR}/CMSIS/Include
        ${DRIVER_DIR}/CMSIS/Device/ST/${MCU_FAMILY}/Include
        ${DRIVER_DIR}/${MCU_FAMILY}_HAL_Driver/Inc
        ${DRIVER_DIR}/${MCU_FAMILY}_HAL_Driver/Inc/Legacy
)

# User source
# Explitly list out source files here
set(USER_SOURCE
        src/main.c
)

# Libraries

# CMSIS START

# This is requried to use CMSIS.
# CMSIS contains the main header files for the family/part that define the registers on the chip

add_library(CMSIS
        ${DRIVER_DIR}/CMSIS/Device/ST/${MCU_FAMILY}/Source/Templates/gcc/startup_${MCU_PART_LOWER}.s
        ${DRIVER_DIR}/CMSIS/Device/ST/${MCU_FAMILY}/Source/Templates/system_${MCU_FAMILY_LOWER}.c)

# CMSIS END

# STM32 LL START

# This is using the LL API only, it's not using the higher level HAL
# If not using the LL API or HAL this whole section can be removed

# Do note moving between families like STM32 L0 to say STM32 F3 or F4 may not have 
# all files listed below or many more thant listed below. This is list is based on the 
# STM32 L0 family

set(HAL_DIR_PREFIX ${DRIVER_DIR}/${MCU_FAMILY}_HAL_Driver/Src/${MCU_FAMILY_LOWER}_ll_)
add_library(HAL
        ${HAL_DIR_PREFIX}adc.c
        ${HAL_DIR_PREFIX}comp.c
        ${HAL_DIR_PREFIX}crc.c
        ${HAL_DIR_PREFIX}crs.c
        ${HAL_DIR_PREFIX}dac.c
        ${HAL_DIR_PREFIX}dma.c
        ${HAL_DIR_PREFIX}exti.c
        ${HAL_DIR_PREFIX}gpio.c
        ${HAL_DIR_PREFIX}i2c.c
        ${HAL_DIR_PREFIX}lptim.c
        ${HAL_DIR_PREFIX}lpuart.c
        ${HAL_DIR_PREFIX}pwr.c
        ${HAL_DIR_PREFIX}rcc.c
        ${HAL_DIR_PREFIX}rng.c
        ${HAL_DIR_PREFIX}rtc.c
        ${HAL_DIR_PREFIX}spi.c
        ${HAL_DIR_PREFIX}tim.c
        ${HAL_DIR_PREFIX}usart.c
        ${HAL_DIR_PREFIX}utils.c
)

# STM32 LL END


add_executable(${PROJECT_NAME}.elf ${USER_SOURCE} ${LINKER_SCRIPT} )

# HAL used on the next line can be removed in the LL API section above is not to be used
target_link_libraries(${PROJECT_NAME}.elf HAL CMSIS)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Map=${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME}.map")
set(HEX_FILE ${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME}.bin)
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMAND ${TOOL_PATH}/arm-none-eabi-size --format=berkeley "${PROJECT_NAME}.elf"
        COMMENT "Building ${HEX_FILE} \nBuilding ${BIN_FILE}")
