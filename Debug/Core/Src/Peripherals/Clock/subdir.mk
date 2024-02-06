################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Peripherals/Clock/peri_clock.c 

OBJS += \
./Core/Src/Peripherals/Clock/peri_clock.o 

C_DEPS += \
./Core/Src/Peripherals/Clock/peri_clock.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Peripherals/Clock/%.o Core/Src/Peripherals/Clock/%.su: ../Core/Src/Peripherals/Clock/%.c Core/Src/Peripherals/Clock/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/Control" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/Peripherals/Clock" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/Peripherals/I2C" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/Peripherals/Radio" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/Peripherals/Status" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/Peripherals/Timer" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/Peripherals/Usart" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/Filter" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/io" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/Main" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/Paramters" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/Peripherals" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/Sensor" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/Telemetry" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Middlewares/Third_Party/FreeRTOS/Source" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Middlewares/Third_Party/FreeRTOS/Source/include" -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Peripherals-2f-Clock

clean-Core-2f-Src-2f-Peripherals-2f-Clock:
	-$(RM) ./Core/Src/Peripherals/Clock/peri_clock.d ./Core/Src/Peripherals/Clock/peri_clock.o ./Core/Src/Peripherals/Clock/peri_clock.su

.PHONY: clean-Core-2f-Src-2f-Peripherals-2f-Clock

