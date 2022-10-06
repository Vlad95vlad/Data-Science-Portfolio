################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Cyclone_TCP/cyclone_tcp/core/bsd_socket.c \
../Cyclone_TCP/cyclone_tcp/core/ethernet.c \
../Cyclone_TCP/cyclone_tcp/core/ethernet_misc.c \
../Cyclone_TCP/cyclone_tcp/core/ip.c \
../Cyclone_TCP/cyclone_tcp/core/net.c \
../Cyclone_TCP/cyclone_tcp/core/net_mem.c \
../Cyclone_TCP/cyclone_tcp/core/net_misc.c \
../Cyclone_TCP/cyclone_tcp/core/nic.c \
../Cyclone_TCP/cyclone_tcp/core/ping.c \
../Cyclone_TCP/cyclone_tcp/core/raw_socket.c \
../Cyclone_TCP/cyclone_tcp/core/socket.c \
../Cyclone_TCP/cyclone_tcp/core/socket_misc.c \
../Cyclone_TCP/cyclone_tcp/core/tcp.c \
../Cyclone_TCP/cyclone_tcp/core/tcp_fsm.c \
../Cyclone_TCP/cyclone_tcp/core/tcp_misc.c \
../Cyclone_TCP/cyclone_tcp/core/tcp_timer.c \
../Cyclone_TCP/cyclone_tcp/core/udp.c 

OBJS += \
./Cyclone_TCP/cyclone_tcp/core/bsd_socket.o \
./Cyclone_TCP/cyclone_tcp/core/ethernet.o \
./Cyclone_TCP/cyclone_tcp/core/ethernet_misc.o \
./Cyclone_TCP/cyclone_tcp/core/ip.o \
./Cyclone_TCP/cyclone_tcp/core/net.o \
./Cyclone_TCP/cyclone_tcp/core/net_mem.o \
./Cyclone_TCP/cyclone_tcp/core/net_misc.o \
./Cyclone_TCP/cyclone_tcp/core/nic.o \
./Cyclone_TCP/cyclone_tcp/core/ping.o \
./Cyclone_TCP/cyclone_tcp/core/raw_socket.o \
./Cyclone_TCP/cyclone_tcp/core/socket.o \
./Cyclone_TCP/cyclone_tcp/core/socket_misc.o \
./Cyclone_TCP/cyclone_tcp/core/tcp.o \
./Cyclone_TCP/cyclone_tcp/core/tcp_fsm.o \
./Cyclone_TCP/cyclone_tcp/core/tcp_misc.o \
./Cyclone_TCP/cyclone_tcp/core/tcp_timer.o \
./Cyclone_TCP/cyclone_tcp/core/udp.o 

C_DEPS += \
./Cyclone_TCP/cyclone_tcp/core/bsd_socket.d \
./Cyclone_TCP/cyclone_tcp/core/ethernet.d \
./Cyclone_TCP/cyclone_tcp/core/ethernet_misc.d \
./Cyclone_TCP/cyclone_tcp/core/ip.d \
./Cyclone_TCP/cyclone_tcp/core/net.d \
./Cyclone_TCP/cyclone_tcp/core/net_mem.d \
./Cyclone_TCP/cyclone_tcp/core/net_misc.d \
./Cyclone_TCP/cyclone_tcp/core/nic.d \
./Cyclone_TCP/cyclone_tcp/core/ping.d \
./Cyclone_TCP/cyclone_tcp/core/raw_socket.d \
./Cyclone_TCP/cyclone_tcp/core/socket.d \
./Cyclone_TCP/cyclone_tcp/core/socket_misc.d \
./Cyclone_TCP/cyclone_tcp/core/tcp.d \
./Cyclone_TCP/cyclone_tcp/core/tcp_fsm.d \
./Cyclone_TCP/cyclone_tcp/core/tcp_misc.d \
./Cyclone_TCP/cyclone_tcp/core/tcp_timer.d \
./Cyclone_TCP/cyclone_tcp/core/udp.d 


# Each subdirectory must supply rules for building sources it contributes
Cyclone_TCP/cyclone_tcp/core/%.o: ../Cyclone_TCP/cyclone_tcp/core/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DUSE_HAL_DRIVER -DINCLUDE_TCP_TERMINAL -DGPL_LICENSE_TERMS_ACCEPTED -DSTM32H753xx -I"D:\Projects\ProjectsEclipse\BC32X" -I"D:\Projects\ProjectsEclipse\BC32X\OthLibs" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\common" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\cyclone_crypto" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\cyclone_ssl" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\cyclone_tcp" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS\portable\GCC\ARM_CM4F" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS\include" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS\portable" -I"D:\Projects\ProjectsEclipse\BC32X\MCU" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\CMSIS" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\CMSIS\Include" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\stm32h7xx_hal_driver" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\stm32h7xx_hal_driver\Inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


