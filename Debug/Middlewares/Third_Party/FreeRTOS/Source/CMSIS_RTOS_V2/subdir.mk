################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.c 

OBJS += \
./Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.o 

C_DEPS += \
./Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/%.o Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/%.su: ../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/%.c Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/Control" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/Peripherals/Clock" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/Peripherals/I2C" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/Peripherals/Radio" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/Peripherals/Status" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/Peripherals/Timer" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/Peripherals/Usart" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/Filter" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/io" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/Main" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/Paramters" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/Peripherals" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/Sensor" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/Telemetry" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Middlewares/Third_Party/FreeRTOS/Source" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Middlewares/Third_Party/FreeRTOS/Source/include" -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-FreeRTOS-2f-Source-2f-CMSIS_RTOS_V2

clean-Middlewares-2f-Third_Party-2f-FreeRTOS-2f-Source-2f-CMSIS_RTOS_V2:
	-$(RM) ./Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.d ./Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.o ./Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-FreeRTOS-2f-Source-2f-CMSIS_RTOS_V2

