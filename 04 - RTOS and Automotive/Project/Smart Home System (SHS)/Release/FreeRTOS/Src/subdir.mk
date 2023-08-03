################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/Src/PollQ.c \
../FreeRTOS/Src/croutine.c \
../FreeRTOS/Src/event_groups.c \
../FreeRTOS/Src/heap_1.c \
../FreeRTOS/Src/integer.c \
../FreeRTOS/Src/list.c \
../FreeRTOS/Src/port.c \
../FreeRTOS/Src/queue.c \
../FreeRTOS/Src/tasks.c 

OBJS += \
./FreeRTOS/Src/PollQ.o \
./FreeRTOS/Src/croutine.o \
./FreeRTOS/Src/event_groups.o \
./FreeRTOS/Src/heap_1.o \
./FreeRTOS/Src/integer.o \
./FreeRTOS/Src/list.o \
./FreeRTOS/Src/port.o \
./FreeRTOS/Src/queue.o \
./FreeRTOS/Src/tasks.o 

C_DEPS += \
./FreeRTOS/Src/PollQ.d \
./FreeRTOS/Src/croutine.d \
./FreeRTOS/Src/event_groups.d \
./FreeRTOS/Src/heap_1.d \
./FreeRTOS/Src/integer.d \
./FreeRTOS/Src/list.d \
./FreeRTOS/Src/port.d \
./FreeRTOS/Src/queue.d \
./FreeRTOS/Src/tasks.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/Src/%.o: ../FreeRTOS/Src/%.c FreeRTOS/Src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\Users\abdel\Documents\Eclipse\Workspace\RTOSApp\Drivers\inc" -I"C:\Users\abdel\Documents\Eclipse\Workspace\RTOSApp\FreeRTOS\Inc" -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


