################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../interface/interface.c 

C_DEPS += \
./interface/interface.d 

OBJS += \
./interface/interface.o 


# Each subdirectory must supply rules for building sources it contributes
interface/%.o: ../interface/%.c interface/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL46Z256VLL4_cm0plus -DCPU_MKL46Z256VLL4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"F:\KL46Project\MKL46Z4_BootLoader\workspace\MKL46Z4_Boot\source" -I"F:\KL46Project\MKL46Z4_BootLoader\workspace\MKL46Z4_Boot\interface" -I"F:\KL46Project\MKL46Z4_BootLoader\workspace\MKL46Z4_Boot\middleware" -I"F:\KL46Project\MKL46Z4_BootLoader\workspace\MKL46Z4_Boot\drivers" -I"F:\KL46Project\MKL46Z4_BootLoader\workspace\MKL46Z4_Boot" -I"F:\KL46Project\MKL46Z4_BootLoader\workspace\MKL46Z4_Boot\CMSIS" -I"F:\KL46Project\MKL46Z4_BootLoader\workspace\MKL46Z4_Boot\startup" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-interface

clean-interface:
	-$(RM) ./interface/interface.d ./interface/interface.o

.PHONY: clean-interface

