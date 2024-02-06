################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Middlewares/Third_Party/FreeRTOS/Source/croutine.c \
../Core/Middlewares/Third_Party/FreeRTOS/Source/event_groups.c \
../Core/Middlewares/Third_Party/FreeRTOS/Source/list.c \
../Core/Middlewares/Third_Party/FreeRTOS/Source/queue.c \
../Core/Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.c \
../Core/Middlewares/Third_Party/FreeRTOS/Source/tasks.c \
../Core/Middlewares/Third_Party/FreeRTOS/Source/timers.c 

OBJS += \
./Core/Middlewares/Third_Party/FreeRTOS/Source/croutine.o \
./Core/Middlewares/Third_Party/FreeRTOS/Source/event_groups.o \
./Core/Middlewares/Third_Party/FreeRTOS/Source/list.o \
./Core/Middlewares/Third_Party/FreeRTOS/Source/queue.o \
./Core/Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.o \
./Core/Middlewares/Third_Party/FreeRTOS/Source/tasks.o \
./Core/Middlewares/Third_Party/FreeRTOS/Source/timers.o 

C_DEPS += \
./Core/Middlewares/Third_Party/FreeRTOS/Source/croutine.d \
./Core/Middlewares/Third_Party/FreeRTOS/Source/event_groups.d \
./Core/Middlewares/Third_Party/FreeRTOS/Source/list.d \
./Core/Middlewares/Third_Party/FreeRTOS/Source/queue.d \
./Core/Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.d \
./Core/Middlewares/Third_Party/FreeRTOS/Source/tasks.d \
./Core/Middlewares/Third_Party/FreeRTOS/Source/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Middlewares/Third_Party/FreeRTOS/Source/%.o Core/Middlewares/Third_Party/FreeRTOS/Source/%.su: ../Core/Middlewares/Third_Party/FreeRTOS/Source/%.c Core/Middlewares/Third_Party/FreeRTOS/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Middlewares-2f-Third_Party-2f-FreeRTOS-2f-Source

clean-Core-2f-Middlewares-2f-Third_Party-2f-FreeRTOS-2f-Source:
	-$(RM) ./Core/Middlewares/Third_Party/FreeRTOS/Source/croutine.d ./Core/Middlewares/Third_Party/FreeRTOS/Source/croutine.o ./Core/Middlewares/Third_Party/FreeRTOS/Source/croutine.su ./Core/Middlewares/Third_Party/FreeRTOS/Source/event_groups.d ./Core/Middlewares/Third_Party/FreeRTOS/Source/event_groups.o ./Core/Middlewares/Third_Party/FreeRTOS/Source/event_groups.su ./Core/Middlewares/Third_Party/FreeRTOS/Source/list.d ./Core/Middlewares/Third_Party/FreeRTOS/Source/list.o ./Core/Middlewares/Third_Party/FreeRTOS/Source/list.su ./Core/Middlewares/Third_Party/FreeRTOS/Source/queue.d ./Core/Middlewares/Third_Party/FreeRTOS/Source/queue.o ./Core/Middlewares/Third_Party/FreeRTOS/Source/queue.su ./Core/Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.d ./Core/Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.o ./Core/Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.su ./Core/Middlewares/Third_Party/FreeRTOS/Source/tasks.d ./Core/Middlewares/Third_Party/FreeRTOS/Source/tasks.o ./Core/Middlewares/Third_Party/FreeRTOS/Source/tasks.su ./Core/Middlewares/Third_Party/FreeRTOS/Source/timers.d ./Core/Middlewares/Third_Party/FreeRTOS/Source/timers.o ./Core/Middlewares/Third_Party/FreeRTOS/Source/timers.su

.PHONY: clean-Core-2f-Middlewares-2f-Third_Party-2f-FreeRTOS-2f-Source

