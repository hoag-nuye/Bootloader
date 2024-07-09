################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/adc.c \
../drivers/clock.c \
../drivers/driverLib.c \
../drivers/gpio.c \
../drivers/mdl2mdl.c \
../drivers/nvic.c \
../drivers/pit.c \
../drivers/port.c \
../drivers/systick.c \
../drivers/tpm.c \
../drivers/uart0.c 

C_DEPS += \
./drivers/adc.d \
./drivers/clock.d \
./drivers/driverLib.d \
./drivers/gpio.d \
./drivers/mdl2mdl.d \
./drivers/nvic.d \
./drivers/pit.d \
./drivers/port.d \
./drivers/systick.d \
./drivers/tpm.d \
./drivers/uart0.d 

OBJS += \
./drivers/adc.o \
./drivers/clock.o \
./drivers/driverLib.o \
./drivers/gpio.o \
./drivers/mdl2mdl.o \
./drivers/nvic.o \
./drivers/pit.o \
./drivers/port.o \
./drivers/systick.o \
./drivers/tpm.o \
./drivers/uart0.o 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL46Z256VLL4_cm0plus -DCPU_MKL46Z256VLL4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"F:\KL46Project\MKL46Z4_BootLoader\workspace\MKL46Z4_App1\source" -I"F:\KL46Project\MKL46Z4_BootLoader\workspace\MKL46Z4_App1\interface" -I"F:\KL46Project\MKL46Z4_BootLoader\workspace\MKL46Z4_App1\middleware" -I"F:\KL46Project\MKL46Z4_BootLoader\workspace\MKL46Z4_App1\drivers" -I"F:\KL46Project\MKL46Z4_BootLoader\workspace\MKL46Z4_App1" -I"F:\KL46Project\MKL46Z4_BootLoader\workspace\MKL46Z4_App1\CMSIS" -I"F:\KL46Project\MKL46Z4_BootLoader\workspace\MKL46Z4_App1\startup" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-drivers

clean-drivers:
	-$(RM) ./drivers/adc.d ./drivers/adc.o ./drivers/clock.d ./drivers/clock.o ./drivers/driverLib.d ./drivers/driverLib.o ./drivers/gpio.d ./drivers/gpio.o ./drivers/mdl2mdl.d ./drivers/mdl2mdl.o ./drivers/nvic.d ./drivers/nvic.o ./drivers/pit.d ./drivers/pit.o ./drivers/port.d ./drivers/port.o ./drivers/systick.d ./drivers/systick.o ./drivers/tpm.d ./drivers/tpm.o ./drivers/uart0.d ./drivers/uart0.o

.PHONY: clean-drivers

