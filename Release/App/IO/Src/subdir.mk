################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/IO/Src/accelerometer.c \
../App/IO/Src/light_sensor.c \
../App/IO/Src/pi_comm.c \
../App/IO/Src/pirs.c \
../App/IO/Src/temp_humidity.c 

OBJS += \
./App/IO/Src/accelerometer.o \
./App/IO/Src/light_sensor.o \
./App/IO/Src/pi_comm.o \
./App/IO/Src/pirs.o \
./App/IO/Src/temp_humidity.o 

C_DEPS += \
./App/IO/Src/accelerometer.d \
./App/IO/Src/light_sensor.d \
./App/IO/Src/pi_comm.d \
./App/IO/Src/pirs.d \
./App/IO/Src/temp_humidity.d 


# Each subdirectory must supply rules for building sources it contributes
App/IO/Src/%.o App/IO/Src/%.su App/IO/Src/%.cyclo: ../App/IO/Src/%.c App/IO/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/graceke02/STM32CubeIDE/workspace_1.19.0/Security_Cam_Only/App/CmdProcessing/Inc" -I"/home/graceke02/STM32CubeIDE/workspace_1.19.0/Security_Cam_Only/App/Hal/Inc" -I"/home/graceke02/STM32CubeIDE/workspace_1.19.0/Security_Cam_Only/App/IO/Inc" -I"/home/graceke02/STM32CubeIDE/workspace_1.19.0/Security_Cam_Only/App/Utilities/Inc" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-App-2f-IO-2f-Src

clean-App-2f-IO-2f-Src:
	-$(RM) ./App/IO/Src/accelerometer.cyclo ./App/IO/Src/accelerometer.d ./App/IO/Src/accelerometer.o ./App/IO/Src/accelerometer.su ./App/IO/Src/light_sensor.cyclo ./App/IO/Src/light_sensor.d ./App/IO/Src/light_sensor.o ./App/IO/Src/light_sensor.su ./App/IO/Src/pi_comm.cyclo ./App/IO/Src/pi_comm.d ./App/IO/Src/pi_comm.o ./App/IO/Src/pi_comm.su ./App/IO/Src/pirs.cyclo ./App/IO/Src/pirs.d ./App/IO/Src/pirs.o ./App/IO/Src/pirs.su ./App/IO/Src/temp_humidity.cyclo ./App/IO/Src/temp_humidity.d ./App/IO/Src/temp_humidity.o ./App/IO/Src/temp_humidity.su

.PHONY: clean-App-2f-IO-2f-Src

