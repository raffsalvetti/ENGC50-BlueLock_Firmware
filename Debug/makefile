################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/util/subdir.mk
-include src/uart/subdir.mk
-include src/pfatfs/subdir.mk
-include src/i2chw/subdir.mk
-include src/ds1307/subdir.mk
-include src/at24c64/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
ENGC50-BlueLock_Firmware.lss \

SIZEDUMMY += \
sizedummy \


# All Target
all: ENGC50-BlueLock_Firmware.elf secondary-outputs

# Tool invocations
ENGC50-BlueLock_Firmware.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,ENGC50-BlueLock_Firmware.map -mmcu=atmega8 -o "ENGC50-BlueLock_Firmware.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ENGC50-BlueLock_Firmware.lss: ENGC50-BlueLock_Firmware.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S ENGC50-BlueLock_Firmware.elf  >"ENGC50-BlueLock_Firmware.lss"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: ENGC50-BlueLock_Firmware.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega8 ENGC50-BlueLock_Firmware.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) ENGC50-BlueLock_Firmware.elf
	-@echo ' '

secondary-outputs: $(LSS) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
