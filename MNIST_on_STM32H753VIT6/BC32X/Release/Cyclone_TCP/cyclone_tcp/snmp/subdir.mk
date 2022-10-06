################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Cyclone_TCP/cyclone_tcp/snmp/snmp_agent.c \
../Cyclone_TCP/cyclone_tcp/snmp/snmp_agent_dispatch.c \
../Cyclone_TCP/cyclone_tcp/snmp/snmp_agent_inform.c \
../Cyclone_TCP/cyclone_tcp/snmp/snmp_agent_message.c \
../Cyclone_TCP/cyclone_tcp/snmp/snmp_agent_misc.c \
../Cyclone_TCP/cyclone_tcp/snmp/snmp_agent_object.c \
../Cyclone_TCP/cyclone_tcp/snmp/snmp_agent_pdu.c \
../Cyclone_TCP/cyclone_tcp/snmp/snmp_agent_trap.c \
../Cyclone_TCP/cyclone_tcp/snmp/snmp_agent_usm.c \
../Cyclone_TCP/cyclone_tcp/snmp/snmp_agent_vacm.c 

OBJS += \
./Cyclone_TCP/cyclone_tcp/snmp/snmp_agent.o \
./Cyclone_TCP/cyclone_tcp/snmp/snmp_agent_dispatch.o \
./Cyclone_TCP/cyclone_tcp/snmp/snmp_agent_inform.o \
./Cyclone_TCP/cyclone_tcp/snmp/snmp_agent_message.o \
./Cyclone_TCP/cyclone_tcp/snmp/snmp_agent_misc.o \
./Cyclone_TCP/cyclone_tcp/snmp/snmp_agent_object.o \
./Cyclone_TCP/cyclone_tcp/snmp/snmp_agent_pdu.o \
./Cyclone_TCP/cyclone_tcp/snmp/snmp_agent_trap.o \
./Cyclone_TCP/cyclone_tcp/snmp/snmp_agent_usm.o \
./Cyclone_TCP/cyclone_tcp/snmp/snmp_agent_vacm.o 

C_DEPS += \
./Cyclone_TCP/cyclone_tcp/snmp/snmp_agent.d \
./Cyclone_TCP/cyclone_tcp/snmp/snmp_agent_dispatch.d \
./Cyclone_TCP/cyclone_tcp/snmp/snmp_agent_inform.d \
./Cyclone_TCP/cyclone_tcp/snmp/snmp_agent_message.d \
./Cyclone_TCP/cyclone_tcp/snmp/snmp_agent_misc.d \
./Cyclone_TCP/cyclone_tcp/snmp/snmp_agent_object.d \
./Cyclone_TCP/cyclone_tcp/snmp/snmp_agent_pdu.d \
./Cyclone_TCP/cyclone_tcp/snmp/snmp_agent_trap.d \
./Cyclone_TCP/cyclone_tcp/snmp/snmp_agent_usm.d \
./Cyclone_TCP/cyclone_tcp/snmp/snmp_agent_vacm.d 


# Each subdirectory must supply rules for building sources it contributes
Cyclone_TCP/cyclone_tcp/snmp/%.o: ../Cyclone_TCP/cyclone_tcp/snmp/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DUSE_HAL_DRIVER -DINCLUDE_TCP_TERMINAL -DGPL_LICENSE_TERMS_ACCEPTED -DSTM32H753xx -I"D:\Projects\ProjectsEclipse\BC32X" -I"D:\Projects\ProjectsEclipse\BC32X\OthLibs" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\common" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\cyclone_crypto" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\cyclone_ssl" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\cyclone_tcp" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS\portable\GCC\ARM_CM4F" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS\include" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS\portable" -I"D:\Projects\ProjectsEclipse\BC32X\MCU" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\CMSIS" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\CMSIS\Include" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\stm32h7xx_hal_driver" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\stm32h7xx_hal_driver\Inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


