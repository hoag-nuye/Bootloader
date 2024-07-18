################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/clock.c \
../drivers/driverLib.c \
../drivers/ftfa.c \
../drivers/gpio.c \
../drivers/nvic.c \
../drivers/pit.c \
../drivers/port.c \
../drivers/systick.c \
../drivers/uart0.c 

C_DEPS += \
./drivers/clock.d \
./drivers/driverLib.d \
./drivers/ftfa.d \
./drivers/gpio.d \
./drivers/nvic.d \
./drivers/pit.d \
./drivers/port.d \
./drivers/systick.d \
./drivers/uart0.d 

OBJS += \
./drivers/clock.o \
./drivers/driverLib.o \
./drivers/ftfa.o \
./drivers/gpio.o \
./drivers/nvic.o \
./drivers/pit.o \
./drivers/port.o \
./drivers/systick.o \
./drivers/uart0.o 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL46Z256VLL4_cm0plus -DCPU_MKL46Z256VLL4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"F:\KL46Project\MKL46Z4_BootLoader\workspace\MKL46Z4_Boot\supports" -I"F:\KL46Project\MKL46Z4_BootLoader\workspace\MKL46Z4_Boot\source" -I"F:\KL46Project\MKL46Z4_BootLoader\workspace\MKL46Z4_Boot\interface" -I"F:\KL46Project\MKL46Z4_BootLoader\workspace\MKL46Z4_Boot\middleware" -I"F:\KL46Project\MKL46Z4_BootLoader\workspace\MKL46Z4_Boot\drivers" -I"F:\KL46Project\MKL46Z4_BootLoader\workspace\MKL46Z4_Boot" -I"F:\KL46Project\MKL46Z4_BootLoader\workspace\MKL46Z4_Boot\CMSIS" -I"F:\KL46Project\MKL46Z4_BootLoader\workspace\MKL46Z4_Boot\startup" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-drivers

clean-drivers:
	-$(RM) ./drivers/clock.d ./drivers/clock.o ./drivers/driverLib.d ./drivers/driverLib.o ./drivers/ftfa.d ./drivers/ftfa.o ./drivers/gpio.d ./drivers/gpio.o ./drivers/nvic.d ./drivers/nvic.o ./drivers/pit.d ./drivers/pit.o ./drivers/port.d ./drivers/port.o ./drivers/systick.d ./drivers/systick.o ./drivers/uart0.d ./drivers/uart0.o

.PHONY: clean-drivers

