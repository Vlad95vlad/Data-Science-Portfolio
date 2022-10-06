################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Cyclone_TCP/cyclone_tcp/ipv4/arp.c \
../Cyclone_TCP/cyclone_tcp/ipv4/auto_ip.c \
../Cyclone_TCP/cyclone_tcp/ipv4/auto_ip_misc.c \
../Cyclone_TCP/cyclone_tcp/ipv4/icmp.c \
../Cyclone_TCP/cyclone_tcp/ipv4/ipv4.c \
../Cyclone_TCP/cyclone_tcp/ipv4/ipv4_frag.c \
../Cyclone_TCP/cyclone_tcp/ipv4/ipv4_misc.c 

OBJS += \
./Cyclone_TCP/cyclone_tcp/ipv4/arp.o \
./Cyclone_TCP/cyclone_tcp/ipv4/auto_ip.o \
./Cyclone_TCP/cyclone_tcp/ipv4/auto_ip_misc.o \
./Cyclone_TCP/cyclone_tcp/ipv4/icmp.o \
./Cyclone_TCP/cyclone_tcp/ipv4/ipv4.o \
./Cyclone_TCP/cyclone_tcp/ipv4/ipv4_frag.o \
./Cyclone_TCP/cyclone_tcp/ipv4/ipv4_misc.o 

C_DEPS += \
./Cyclone_TCP/cyclone_tcp/ipv4/arp.d \
./Cyclone_TCP/cyclone_tcp/ipv4/auto_ip.d \
./Cyclone_TCP/cyclone_tcp/ipv4/auto_ip_misc.d \
./Cyclone_TCP/cyclone_tcp/ipv4/icmp.d \
./Cyclone_TCP/cyclone_tcp/ipv4/ipv4.d \
./Cyclone_TCP/cyclone_tcp/ipv4/ipv4_frag.d \
./Cyclone_TCP/cyclone_tcp/ipv4/ipv4_misc.d 


# Each subdirectory must supply rules for building sources it contributes
Cyclone_TCP/cyclone_tcp/ipv4/%.o: ../Cyclone_TCP/cyclone_tcp/ipv4/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DUSE_HAL_DRIVER -DINCLUDE_TCP_TERMINAL -DGPL_LICENSE_TERMS_ACCEPTED -DSTM32H753xx -I"D:\Projects\ProjectsEclipse\BC32X" -I"D:\Projects\ProjectsEclipse\BC32X\OthLibs" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\common" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\cyclone_crypto" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\cyclone_ssl" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\cyclone_tcp" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS\portable\GCC\ARM_CM4F" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS\include" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS\portable" -I"D:\Projects\ProjectsEclipse\BC32X\MCU" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\CMSIS" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\CMSIS\Include" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\stm32h7xx_hal_driver" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\stm32h7xx_hal_driver\Inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


