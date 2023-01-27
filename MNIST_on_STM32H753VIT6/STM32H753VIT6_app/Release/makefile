################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include OthLibs/subdir.mk
-include MCU/stm32h7xx_hal_driver/Src/subdir.mk
-include MCU/CMSIS/subdir.mk
-include FreeRTOS/portable/MemMang/subdir.mk
-include FreeRTOS/portable/GCC/ARM_CM4F/subdir.mk
-include FreeRTOS/subdir.mk
-include Cyclone_TCP/cyclone_tcp/web_socket/subdir.mk
-include Cyclone_TCP/cyclone_tcp/tftp/subdir.mk
-include Cyclone_TCP/cyclone_tcp/sntp/subdir.mk
-include Cyclone_TCP/cyclone_tcp/snmp/subdir.mk
-include Cyclone_TCP/cyclone_tcp/ppp/subdir.mk
-include Cyclone_TCP/cyclone_tcp/netbios/subdir.mk
-include Cyclone_TCP/cyclone_tcp/mqtt/subdir.mk
-include Cyclone_TCP/cyclone_tcp/mibs/subdir.mk
-include Cyclone_TCP/cyclone_tcp/mdns/subdir.mk
-include Cyclone_TCP/cyclone_tcp/llmnr/subdir.mk
-include Cyclone_TCP/cyclone_tcp/ipv6/subdir.mk
-include Cyclone_TCP/cyclone_tcp/ipv4/subdir.mk
-include Cyclone_TCP/cyclone_tcp/igmp/subdir.mk
-include Cyclone_TCP/cyclone_tcp/icecast/subdir.mk
-include Cyclone_TCP/cyclone_tcp/http/subdir.mk
-include Cyclone_TCP/cyclone_tcp/drivers/phy/subdir.mk
-include Cyclone_TCP/cyclone_tcp/drivers/mac/subdir.mk
-include Cyclone_TCP/cyclone_tcp/dns_sd/subdir.mk
-include Cyclone_TCP/cyclone_tcp/dns/subdir.mk
-include Cyclone_TCP/cyclone_tcp/dhcpv6/subdir.mk
-include Cyclone_TCP/cyclone_tcp/dhcp/subdir.mk
-include Cyclone_TCP/cyclone_tcp/core/subdir.mk
-include Cyclone_TCP/cyclone_tcp/coap/subdir.mk
-include Cyclone_TCP/cyclone_ssl/subdir.mk
-include Cyclone_TCP/cyclone_crypto/xof/subdir.mk
-include Cyclone_TCP/cyclone_crypto/rng/subdir.mk
-include Cyclone_TCP/cyclone_crypto/pkix/subdir.mk
-include Cyclone_TCP/cyclone_crypto/pkc/subdir.mk
-include Cyclone_TCP/cyclone_crypto/mpi/subdir.mk
-include Cyclone_TCP/cyclone_crypto/mac/subdir.mk
-include Cyclone_TCP/cyclone_crypto/kdf/subdir.mk
-include Cyclone_TCP/cyclone_crypto/hash/subdir.mk
-include Cyclone_TCP/cyclone_crypto/hardware/subdir.mk
-include Cyclone_TCP/cyclone_crypto/encoding/subdir.mk
-include Cyclone_TCP/cyclone_crypto/ecc/subdir.mk
-include Cyclone_TCP/cyclone_crypto/cipher_mode/subdir.mk
-include Cyclone_TCP/cyclone_crypto/cipher/subdir.mk
-include Cyclone_TCP/cyclone_crypto/aead/subdir.mk
-include Cyclone_TCP/common/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
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
SECONDARY_FLASH += \
BC32X.hex \

SECONDARY_SIZE += \
BC32X.siz \


# All Target
all: BC32X.elf secondary-outputs

# Tool invocations
BC32X.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU Arm Cross C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -T "D:\Projects\ProjectsEclipse\BC32X\MCU\stm32h753_flash.ld" -Xlinker --gc-sections -Wl,-Map,"BC32X.map" --specs=nano.specs -o "BC32X.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

BC32X.hex: BC32X.elf
	@echo 'Invoking: GNU Arm Cross Create Flash Image'
	arm-none-eabi-objcopy -O ihex "BC32X.elf"  "BC32X.hex"
	@echo 'Finished building: $@'
	@echo ' '

BC32X.siz: BC32X.elf
	@echo 'Invoking: GNU Arm Cross Print Size'
	arm-none-eabi-size --format=berkeley "BC32X.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) BC32X.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
