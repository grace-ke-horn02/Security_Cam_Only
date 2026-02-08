################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/App/Hal/Src/stm_hal.c 

OBJS += \
./Core/App/Hal/Src/stm_hal.o 

C_DEPS += \
./Core/App/Hal/Src/stm_hal.d 


# Each subdirectory must supply rules for building sources it contributes
Core/App/Hal/Src/%.o Core/App/Hal/Src/%.su Core/App/Hal/Src/%.cyclo: ../Core/App/Hal/Src/%.c Core/App/Hal/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I"/home/graceke02/STM32CubeIDE/workspace_1.19.0/Security_Cam_Only/Core/App/CmdProcessing/Inc" -I"/home/graceke02/STM32CubeIDE/workspace_1.19.0/Security_Cam_Only/Core/App/Hal/Inc" -I"/home/graceke02/STM32CubeIDE/workspace_1.19.0/Security_Cam_Only/Core/App/IO/Inc" -I"/home/graceke02/STM32CubeIDE/workspace_1.19.0/Security_Cam_Only/Core/App/Utilities/Inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-App-2f-Hal-2f-Src

clean-Core-2f-App-2f-Hal-2f-Src:
	-$(RM) ./Core/App/Hal/Src/stm_hal.cyclo ./Core/App/Hal/Src/stm_hal.d ./Core/App/Hal/Src/stm_hal.o ./Core/App/Hal/Src/stm_hal.su

.PHONY: clean-Core-2f-App-2f-Hal-2f-Src

