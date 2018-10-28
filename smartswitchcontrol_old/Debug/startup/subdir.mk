################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../startup/startup_stm32l1xx_md.S 

OBJS += \
./startup/startup_stm32l1xx_md.o 

S_UPPER_DEPS += \
./startup/startup_stm32l1xx_md.d 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DSTM32 -DSTM32L1 -DSTM32L152RBTx -DSTM32L_DISCOVERY -DDEBUG -DSTM32L1XX_MD -DUSE_STDPERIPH_DRIVER -I"D:/work/Eclipse/smartswitchcontrol/Utilities" -I"D:/work/Eclipse/smartswitchcontrol/StdPeriph_Driver/inc" -I"D:/work/Eclipse/smartswitchcontrol/inc" -I"D:/work/Eclipse/smartswitchcontrol/CMSIS/device" -I"D:/work/Eclipse/smartswitchcontrol/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


