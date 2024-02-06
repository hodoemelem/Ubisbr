################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/freertos.c \
../Core/Src/stm32l4xx_hal_msp.c \
../Core/Src/stm32l4xx_hal_timebase_tim.c \
../Core/Src/stm32l4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32l4xx.c 

OBJS += \
./Core/Src/freertos.o \
./Core/Src/stm32l4xx_hal_msp.o \
./Core/Src/stm32l4xx_hal_timebase_tim.o \
./Core/Src/stm32l4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32l4xx.o 

C_DEPS += \
./Core/Src/freertos.d \
./Core/Src/stm32l4xx_hal_msp.d \
./Core/Src/stm32l4xx_hal_timebase_tim.d \
./Core/Src/stm32l4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32l4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/Control" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/Peripherals/Clock" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/Peripherals/I2C" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/Peripherals/Radio" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/Peripherals/Status" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/Peripherals/Timer" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/Peripherals/Usart" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/Filter" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/io" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/Main" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/Paramters" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/Peripherals" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/Sensor" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/Telemetry" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Middlewares/Third_Party/FreeRTOS/Source" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Middlewares/Third_Party/FreeRTOS/Source/include" -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/freertos.d ./Core/Src/freertos.o ./Core/Src/freertos.su ./Core/Src/stm32l4xx_hal_msp.d ./Core/Src/stm32l4xx_hal_msp.o ./Core/Src/stm32l4xx_hal_msp.su ./Core/Src/stm32l4xx_hal_timebase_tim.d ./Core/Src/stm32l4xx_hal_timebase_tim.o ./Core/Src/stm32l4xx_hal_timebase_tim.su ./Core/Src/stm32l4xx_it.d ./Core/Src/stm32l4xx_it.o ./Core/Src/stm32l4xx_it.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32l4xx.d ./Core/Src/system_stm32l4xx.o ./Core/Src/system_stm32l4xx.su

.PHONY: clean-Core-2f-Src

