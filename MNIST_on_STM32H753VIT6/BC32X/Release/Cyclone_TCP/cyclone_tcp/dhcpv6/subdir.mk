################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Cyclone_TCP/cyclone_tcp/dhcpv6/dhcpv6_client.c \
../Cyclone_TCP/cyclone_tcp/dhcpv6/dhcpv6_client_fsm.c \
../Cyclone_TCP/cyclone_tcp/dhcpv6/dhcpv6_client_misc.c \
../Cyclone_TCP/cyclone_tcp/dhcpv6/dhcpv6_common.c \
../Cyclone_TCP/cyclone_tcp/dhcpv6/dhcpv6_debug.c \
../Cyclone_TCP/cyclone_tcp/dhcpv6/dhcpv6_relay.c 

OBJS += \
./Cyclone_TCP/cyclone_tcp/dhcpv6/dhcpv6_client.o \
./Cyclone_TCP/cyclone_tcp/dhcpv6/dhcpv6_client_fsm.o \
./Cyclone_TCP/cyclone_tcp/dhcpv6/dhcpv6_client_misc.o \
./Cyclone_TCP/cyclone_tcp/dhcpv6/dhcpv6_common.o \
./Cyclone_TCP/cyclone_tcp/dhcpv6/dhcpv6_debug.o \
./Cyclone_TCP/cyclone_tcp/dhcpv6/dhcpv6_relay.o 

C_DEPS += \
./Cyclone_TCP/cyclone_tcp/dhcpv6/dhcpv6_client.d \
./Cyclone_TCP/cyclone_tcp/dhcpv6/dhcpv6_client_fsm.d \
./Cyclone_TCP/cyclone_tcp/dhcpv6/dhcpv6_client_misc.d \
./Cyclone_TCP/cyclone_tcp/dhcpv6/dhcpv6_common.d \
./Cyclone_TCP/cyclone_tcp/dhcpv6/dhcpv6_debug.d \
./Cyclone_TCP/cyclone_tcp/dhcpv6/dhcpv6_relay.d 


# Each subdirectory must supply rules for building sources it contributes
Cyclone_TCP/cyclone_tcp/dhcpv6/%.o: ../Cyclone_TCP/cyclone_tcp/dhcpv6/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DUSE_HAL_DRIVER -DINCLUDE_TCP_TERMINAL -DGPL_LICENSE_TERMS_ACCEPTED -DSTM32H753xx -I"D:\Projects\ProjectsEclipse\BC32X" -I"D:\Projects\ProjectsEclipse\BC32X\OthLibs" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\common" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\cyclone_crypto" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\cyclone_ssl" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\cyclone_tcp" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS\portable\GCC\ARM_CM4F" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS\include" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS\portable" -I"D:\Projects\ProjectsEclipse\BC32X\MCU" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\CMSIS" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\CMSIS\Include" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\stm32h7xx_hal_driver" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\stm32h7xx_hal_driver\Inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


