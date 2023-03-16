################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MYRTOS/CortexMX_OS_porting.c \
../MYRTOS/My_RTOS_FIFO.c \
../MYRTOS/scheduler.c 

OBJS += \
./MYRTOS/CortexMX_OS_porting.o \
./MYRTOS/My_RTOS_FIFO.o \
./MYRTOS/scheduler.o 

C_DEPS += \
./MYRTOS/CortexMX_OS_porting.d \
./MYRTOS/My_RTOS_FIFO.d \
./MYRTOS/scheduler.d 


# Each subdirectory must supply rules for building sources it contributes
MYRTOS/CortexMX_OS_porting.o: ../MYRTOS/CortexMX_OS_porting.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I"C:/Users/ayman/STM32CubeIDE/workspace_1.4.0/RTOS/MYRTOS/inc" -I../Inc -I"C:/Users/ayman/STM32CubeIDE/workspace_1.4.0/RTOS/CMSIS_V5" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MYRTOS/CortexMX_OS_porting.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
MYRTOS/My_RTOS_FIFO.o: ../MYRTOS/My_RTOS_FIFO.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I"C:/Users/ayman/STM32CubeIDE/workspace_1.4.0/RTOS/MYRTOS/inc" -I../Inc -I"C:/Users/ayman/STM32CubeIDE/workspace_1.4.0/RTOS/CMSIS_V5" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MYRTOS/My_RTOS_FIFO.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
MYRTOS/scheduler.o: ../MYRTOS/scheduler.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I"C:/Users/ayman/STM32CubeIDE/workspace_1.4.0/RTOS/MYRTOS/inc" -I../Inc -I"C:/Users/ayman/STM32CubeIDE/workspace_1.4.0/RTOS/CMSIS_V5" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MYRTOS/scheduler.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

