################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/pfatfs/diskio.c \
../src/pfatfs/mmc.c \
../src/pfatfs/pff.c 

S_UPPER_SRCS += \
../src/pfatfs/usi.S 

OBJS += \
./src/pfatfs/diskio.o \
./src/pfatfs/mmc.o \
./src/pfatfs/pff.o \
./src/pfatfs/usi.o 

C_DEPS += \
./src/pfatfs/diskio.d \
./src/pfatfs/mmc.d \
./src/pfatfs/pff.d 

S_UPPER_DEPS += \
./src/pfatfs/usi.d 


# Each subdirectory must supply rules for building sources it contributes
src/pfatfs/%.o: ../src/pfatfs/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega8 -DF_CPU=12000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/pfatfs/%.o: ../src/pfatfs/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Assembler'
	avr-gcc -x assembler-with-cpp -mmcu=atmega8 -DF_CPU=12000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


