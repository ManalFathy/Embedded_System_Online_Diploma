################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lifo.c \
../main.c 

C_DEPS += \
./lifo.d \
./main.d 

OBJS += \
./lifo.o \
./main.o 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I"::\" -I"C:\WS_EmbDip\ECLIPSE_WS\LIFO_Buffer_old\lifo.h" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean--2e-

clean--2e-:
	-$(RM) ./lifo.d ./lifo.o ./main.d ./main.o

.PHONY: clean--2e-

