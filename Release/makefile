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
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
ENGC50-TrancaEletronica_Firmware.lss \

FLASH_IMAGE += \
ENGC50-TrancaEletronica_Firmware.hex \

EEPROM_IMAGE += \
ENGC50-TrancaEletronica_Firmware.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: ENGC50-TrancaEletronica_Firmware.elf secondary-outputs

# Tool invocations
ENGC50-TrancaEletronica_Firmware.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,ENGC50-TrancaEletronica_Firmware.map -mmcu=atmega8 -o "ENGC50-TrancaEletronica_Firmware.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ENGC50-TrancaEletronica_Firmware.lss: ENGC50-TrancaEletronica_Firmware.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S ENGC50-TrancaEletronica_Firmware.elf  >"ENGC50-TrancaEletronica_Firmware.lss"
	@echo 'Finished building: $@'
	@echo ' '

ENGC50-TrancaEletronica_Firmware.hex: ENGC50-TrancaEletronica_Firmware.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex ENGC50-TrancaEletronica_Firmware.elf  "ENGC50-TrancaEletronica_Firmware.hex"
	@echo 'Finished building: $@'
	@echo ' '

ENGC50-TrancaEletronica_Firmware.eep: ENGC50-TrancaEletronica_Firmware.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex ENGC50-TrancaEletronica_Firmware.elf  "ENGC50-TrancaEletronica_Firmware.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: ENGC50-TrancaEletronica_Firmware.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega8 ENGC50-TrancaEletronica_Firmware.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) ENGC50-TrancaEletronica_Firmware.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
