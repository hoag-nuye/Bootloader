################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../amazon-freertos/FreeRTOS/event_groups.c \
../amazon-freertos/FreeRTOS/list.c \
../amazon-freertos/FreeRTOS/queue.c \
../amazon-freertos/FreeRTOS/stream_buffer.c \
../amazon-freertos/FreeRTOS/tasks.c \
../amazon-freertos/FreeRTOS/timers.c 

C_DEPS += \
./amazon-freertos/FreeRTOS/event_groups.d \
./amazon-freertos/FreeRTOS/list.d \
./amazon-freertos/FreeRTOS/queue.d \
./amazon-freertos/FreeRTOS/stream_buffer.d \
./amazon-freertos/FreeRTOS/tasks.d \
./amazon-freertos/FreeRTOS/timers.d 

OBJS += \
./amazon-freertos/FreeRTOS/event_groups.o \
./amazon-freertos/FreeRTOS/list.o \
./amazon-freertos/FreeRTOS/queue.o \
./amazon-freertos/FreeRTOS/stream_buffer.o \
./amazon-freertos/FreeRTOS/tasks.o \
./amazon-freertos/FreeRTOS/timers.o 


# Each subdirectory must supply rules for building sources it contributes
amazon-freertos/FreeRTOS/%.o: ../amazon-freertos/FreeRTOS/%.c amazon-freertos/FreeRTOS/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL46Z256VLL4_cm0plus -DCPU_MKL46Z256VLL4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"F:\KL46Project\MKL46Z4_BootLoader\workspace\MKL46Z4_App2\source" -I"F:\KL46Project\MKL46Z4_BootLoader\workspace\MKL46Z4_App2" -I"F:\KL46Project\MKL46Z4_BootLoader\workspace\MKL46Z4_App2\CMSIS" -I"F:\KL46Project\MKL46Z4_BootLoader\workspace\MKL46Z4_App2\drivers" -I"F:\KL46Project\MKL46Z4_BootLoader\workspace\MKL46Z4_App2\amazon-freertos\FreeRTOS\portable" -I"F:\KL46Project\MKL46Z4_BootLoader\workspace\MKL46Z4_App2\freertos\portable" -I"F:\KL46Project\MKL46Z4_BootLoader\workspace\MKL46Z4_App2\amazon-freertos\include" -I"F:\KL46Project\MKL46Z4_BootLoader\workspace\MKL46Z4_App2\startup" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-amazon-2d-freertos-2f-FreeRTOS

clean-amazon-2d-freertos-2f-FreeRTOS:
	-$(RM) ./amazon-freertos/FreeRTOS/event_groups.d ./amazon-freertos/FreeRTOS/event_groups.o ./amazon-freertos/FreeRTOS/list.d ./amazon-freertos/FreeRTOS/list.o ./amazon-freertos/FreeRTOS/queue.d ./amazon-freertos/FreeRTOS/queue.o ./amazon-freertos/FreeRTOS/stream_buffer.d ./amazon-freertos/FreeRTOS/stream_buffer.o ./amazon-freertos/FreeRTOS/tasks.d ./amazon-freertos/FreeRTOS/tasks.o ./amazon-freertos/FreeRTOS/timers.d ./amazon-freertos/FreeRTOS/timers.o

.PHONY: clean-amazon-2d-freertos-2f-FreeRTOS

