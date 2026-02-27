################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Hal/Src/stm_hal.c 

OBJS += \
./App/Hal/Src/stm_hal.o 

C_DEPS += \
./App/Hal/Src/stm_hal.d 


# Each subdirectory must supply rules for building sources it contributes
App/Hal/Src/%.o App/Hal/Src/%.su App/Hal/Src/%.cyclo: ../App/Hal/Src/%.c App/Hal/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/graceke02/STM32CubeIDE/workspace_1.19.0/Security_Cam_Only/App/CmdProcessing/Inc" -I"/home/graceke02/STM32CubeIDE/workspace_1.19.0/Security_Cam_Only/App/Hal/Inc" -I"/home/graceke02/STM32CubeIDE/workspace_1.19.0/Security_Cam_Only/App/IO/Inc" -I"/home/graceke02/STM32CubeIDE/workspace_1.19.0/Security_Cam_Only/App/Utilities/Inc" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-App-2f-Hal-2f-Src

clean-App-2f-Hal-2f-Src:
	-$(RM) ./App/Hal/Src/stm_hal.cyclo ./App/Hal/Src/stm_hal.d ./App/Hal/Src/stm_hal.o ./App/Hal/Src/stm_hal.su

.PHONY: clean-App-2f-Hal-2f-Src

