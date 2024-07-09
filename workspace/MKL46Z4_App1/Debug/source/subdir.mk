################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/MKL46Z4_LightSensor.c \
../source/mtb.c 

C_DEPS += \
./source/MKL46Z4_LightSensor.d \
./source/mtb.d 

OBJS += \
./source/MKL46Z4_LightSensor.o \
./source/mtb.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL46Z256VLL4_cm0plus -DCPU_MKL46Z256VLL4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"F:\KL46Project\MKL46Z4_BootLoader\workspace\MKL46Z4_App1\source" -I"F:\KL46Project\MKL46Z4_BootLoader\workspace\MKL46Z4_App1\interface" -I"F:\KL46Project\MKL46Z4_BootLoader\workspace\MKL46Z4_App1\middleware" -I"F:\KL46Project\MKL46Z4_BootLoader\workspace\MKL46Z4_App1\drivers" -I"F:\KL46Project\MKL46Z4_BootLoader\workspace\MKL46Z4_App1" -I"F:\KL46Project\MKL46Z4_BootLoader\workspace\MKL46Z4_App1\CMSIS" -I"F:\KL46Project\MKL46Z4_BootLoader\workspace\MKL46Z4_App1\startup" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/MKL46Z4_LightSensor.d ./source/MKL46Z4_LightSensor.o ./source/mtb.d ./source/mtb.o

.PHONY: clean-source

