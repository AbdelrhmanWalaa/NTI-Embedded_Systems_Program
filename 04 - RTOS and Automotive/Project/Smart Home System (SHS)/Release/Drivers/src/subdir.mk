################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/src/ADC.c \
../Drivers/src/BasicIO.c \
../Drivers/src/Ext_int.c \
../Drivers/src/LCD.c \
../Drivers/src/SPI.c \
../Drivers/src/TWI.c \
../Drivers/src/keypad.c \
../Drivers/src/seg.c \
../Drivers/src/timer.c \
../Drivers/src/uart.c 

OBJS += \
./Drivers/src/ADC.o \
./Drivers/src/BasicIO.o \
./Drivers/src/Ext_int.o \
./Drivers/src/LCD.o \
./Drivers/src/SPI.o \
./Drivers/src/TWI.o \
./Drivers/src/keypad.o \
./Drivers/src/seg.o \
./Drivers/src/timer.o \
./Drivers/src/uart.o 

C_DEPS += \
./Drivers/src/ADC.d \
./Drivers/src/BasicIO.d \
./Drivers/src/Ext_int.d \
./Drivers/src/LCD.d \
./Drivers/src/SPI.d \
./Drivers/src/TWI.d \
./Drivers/src/keypad.d \
./Drivers/src/seg.d \
./Drivers/src/timer.d \
./Drivers/src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/src/%.o: ../Drivers/src/%.c Drivers/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\Users\abdel\Documents\Eclipse\Workspace\RTOSApp\Drivers\inc" -I"C:\Users\abdel\Documents\Eclipse\Workspace\RTOSApp\FreeRTOS\Inc" -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


