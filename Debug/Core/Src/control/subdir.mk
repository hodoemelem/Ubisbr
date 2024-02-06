################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/control/controller.c \
../Core/Src/control/pid_controller.c 

OBJS += \
./Core/Src/control/controller.o \
./Core/Src/control/pid_controller.o 

C_DEPS += \
./Core/Src/control/controller.d \
./Core/Src/control/pid_controller.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/control/%.o Core/Src/control/%.su: ../Core/Src/control/%.c Core/Src/control/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src/control" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Core/Src" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Middlewares/Third_Party/FreeRTOS/Source" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2" -I"/home/henry/Desktop/ubiSBR/ubiSBR/Middlewares/Third_Party/FreeRTOS/Source/include" -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-control

clean-Core-2f-Src-2f-control:
	-$(RM) ./Core/Src/control/controller.d ./Core/Src/control/controller.o ./Core/Src/control/controller.su ./Core/Src/control/pid_controller.d ./Core/Src/control/pid_controller.o ./Core/Src/control/pid_controller.su

.PHONY: clean-Core-2f-Src-2f-control

