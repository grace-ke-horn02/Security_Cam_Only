################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/App/IO/Src/accelerometer.c \
../Core/App/IO/Src/light_sensor.c \
../Core/App/IO/Src/pi_comm.c \
../Core/App/IO/Src/pirs.c \
../Core/App/IO/Src/temp_humidity.c 

OBJS += \
./Core/App/IO/Src/accelerometer.o \
./Core/App/IO/Src/light_sensor.o \
./Core/App/IO/Src/pi_comm.o \
./Core/App/IO/Src/pirs.o \
./Core/App/IO/Src/temp_humidity.o 

C_DEPS += \
./Core/App/IO/Src/accelerometer.d \
./Core/App/IO/Src/light_sensor.d \
./Core/App/IO/Src/pi_comm.d \
./Core/App/IO/Src/pirs.d \
./Core/App/IO/Src/temp_humidity.d 


# Each subdirectory must supply rules for building sources it contributes
Core/App/IO/Src/%.o Core/App/IO/Src/%.su Core/App/IO/Src/%.cyclo: ../Core/App/IO/Src/%.c Core/App/IO/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I"/home/graceke02/STM32CubeIDE/workspace_1.19.0/Security_Cam_Only/Core/App/CmdProcessing/Inc" -I"/home/graceke02/STM32CubeIDE/workspace_1.19.0/Security_Cam_Only/Core/App/Hal/Inc" -I"/home/graceke02/STM32CubeIDE/workspace_1.19.0/Security_Cam_Only/Core/App/IO/Inc" -I"/home/graceke02/STM32CubeIDE/workspace_1.19.0/Security_Cam_Only/Core/App/Utilities/Inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-App-2f-IO-2f-Src

clean-Core-2f-App-2f-IO-2f-Src:
	-$(RM) ./Core/App/IO/Src/accelerometer.cyclo ./Core/App/IO/Src/accelerometer.d ./Core/App/IO/Src/accelerometer.o ./Core/App/IO/Src/accelerometer.su ./Core/App/IO/Src/light_sensor.cyclo ./Core/App/IO/Src/light_sensor.d ./Core/App/IO/Src/light_sensor.o ./Core/App/IO/Src/light_sensor.su ./Core/App/IO/Src/pi_comm.cyclo ./Core/App/IO/Src/pi_comm.d ./Core/App/IO/Src/pi_comm.o ./Core/App/IO/Src/pi_comm.su ./Core/App/IO/Src/pirs.cyclo ./Core/App/IO/Src/pirs.d ./Core/App/IO/Src/pirs.o ./Core/App/IO/Src/pirs.su ./Core/App/IO/Src/temp_humidity.cyclo ./Core/App/IO/Src/temp_humidity.d ./Core/App/IO/Src/temp_humidity.o ./Core/App/IO/Src/temp_humidity.su

.PHONY: clean-Core-2f-App-2f-IO-2f-Src

