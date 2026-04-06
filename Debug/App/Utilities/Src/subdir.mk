################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Utilities/Src/bit_manipulation.c 

OBJS += \
./App/Utilities/Src/bit_manipulation.o 

C_DEPS += \
./App/Utilities/Src/bit_manipulation.d 


# Each subdirectory must supply rules for building sources it contributes
App/Utilities/Src/%.o App/Utilities/Src/%.su App/Utilities/Src/%.cyclo: ../App/Utilities/Src/%.c App/Utilities/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../App/Hal/Inc -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/graceke02/STM32CubeIDE/workspace_1.19.0/Security_Cam_Only/App/CmdProcessing/Inc" -I"/home/graceke02/STM32CubeIDE/workspace_1.19.0/Security_Cam_Only/App/IO/Inc" -I"/home/graceke02/STM32CubeIDE/workspace_1.19.0/Security_Cam_Only/App/Utilities/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-App-2f-Utilities-2f-Src

clean-App-2f-Utilities-2f-Src:
	-$(RM) ./App/Utilities/Src/bit_manipulation.cyclo ./App/Utilities/Src/bit_manipulation.d ./App/Utilities/Src/bit_manipulation.o ./App/Utilities/Src/bit_manipulation.su

.PHONY: clean-App-2f-Utilities-2f-Src

