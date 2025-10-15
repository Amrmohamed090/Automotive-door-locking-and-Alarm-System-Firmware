################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../EXTI/EXTI.c 

OBJS += \
./EXTI/EXTI.o 

C_DEPS += \
./EXTI/EXTI.d 


# Each subdirectory must supply rules for building sources it contributes
EXTI/%.o: ../EXTI/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g -DNDEBUG -DSTM32F401xE -DHSE_VALUE=8000000 -I"../include" -I"D:\imt\ARM\ARM_WS\Lab4_Startup_Project_TODO\GPT" -I"D:\imt\ARM\ARM_WS\Lab4_Startup_Project_TODO\EXTI" -I"D:\imt\ARM\ARM_WS\Lab4_Startup_Project_TODO\keypad" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -I"D:\imt\ARM\ARM_WS\Lab4_Startup_Project_TODO\Lib" -I"D:\imt\ARM\ARM_WS\Lab4_Startup_Project_TODO\Rcc" -I"D:\imt\ARM\ARM_WS\Lab4_Startup_Project_TODO\Gpio" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


