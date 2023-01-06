################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/Src/keypad.c \
../HAL/Src/lcd.c 

OBJS += \
./HAL/Src/keypad.o \
./HAL/Src/lcd.o 

C_DEPS += \
./HAL/Src/keypad.d \
./HAL/Src/lcd.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/Src/keypad.o: ../HAL/Src/keypad.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/ayman/STM32CubeIDE/workspace_1.4.0/Drivers/HAL/includes" -I"C:/Users/ayman/STM32CubeIDE/workspace_1.4.0/Drivers/Stm32_F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/Src/keypad.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
HAL/Src/lcd.o: ../HAL/Src/lcd.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/ayman/STM32CubeIDE/workspace_1.4.0/Drivers/HAL/includes" -I"C:/Users/ayman/STM32CubeIDE/workspace_1.4.0/Drivers/Stm32_F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/Src/lcd.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

