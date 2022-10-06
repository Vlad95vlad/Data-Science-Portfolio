################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Cyclone_TCP/cyclone_tcp/ppp/chap.c \
../Cyclone_TCP/cyclone_tcp/ppp/ipcp.c \
../Cyclone_TCP/cyclone_tcp/ppp/ipv6cp.c \
../Cyclone_TCP/cyclone_tcp/ppp/lcp.c \
../Cyclone_TCP/cyclone_tcp/ppp/pap.c \
../Cyclone_TCP/cyclone_tcp/ppp/ppp.c \
../Cyclone_TCP/cyclone_tcp/ppp/ppp_debug.c \
../Cyclone_TCP/cyclone_tcp/ppp/ppp_fsm.c \
../Cyclone_TCP/cyclone_tcp/ppp/ppp_hdlc.c \
../Cyclone_TCP/cyclone_tcp/ppp/ppp_misc.c 

OBJS += \
./Cyclone_TCP/cyclone_tcp/ppp/chap.o \
./Cyclone_TCP/cyclone_tcp/ppp/ipcp.o \
./Cyclone_TCP/cyclone_tcp/ppp/ipv6cp.o \
./Cyclone_TCP/cyclone_tcp/ppp/lcp.o \
./Cyclone_TCP/cyclone_tcp/ppp/pap.o \
./Cyclone_TCP/cyclone_tcp/ppp/ppp.o \
./Cyclone_TCP/cyclone_tcp/ppp/ppp_debug.o \
./Cyclone_TCP/cyclone_tcp/ppp/ppp_fsm.o \
./Cyclone_TCP/cyclone_tcp/ppp/ppp_hdlc.o \
./Cyclone_TCP/cyclone_tcp/ppp/ppp_misc.o 

C_DEPS += \
./Cyclone_TCP/cyclone_tcp/ppp/chap.d \
./Cyclone_TCP/cyclone_tcp/ppp/ipcp.d \
./Cyclone_TCP/cyclone_tcp/ppp/ipv6cp.d \
./Cyclone_TCP/cyclone_tcp/ppp/lcp.d \
./Cyclone_TCP/cyclone_tcp/ppp/pap.d \
./Cyclone_TCP/cyclone_tcp/ppp/ppp.d \
./Cyclone_TCP/cyclone_tcp/ppp/ppp_debug.d \
./Cyclone_TCP/cyclone_tcp/ppp/ppp_fsm.d \
./Cyclone_TCP/cyclone_tcp/ppp/ppp_hdlc.d \
./Cyclone_TCP/cyclone_tcp/ppp/ppp_misc.d 


# Each subdirectory must supply rules for building sources it contributes
Cyclone_TCP/cyclone_tcp/ppp/%.o: ../Cyclone_TCP/cyclone_tcp/ppp/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DUSE_HAL_DRIVER -DINCLUDE_TCP_TERMINAL -DGPL_LICENSE_TERMS_ACCEPTED -DSTM32H753xx -I"D:\Projects\ProjectsEclipse\BC32X" -I"D:\Projects\ProjectsEclipse\BC32X\OthLibs" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\common" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\cyclone_crypto" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\cyclone_ssl" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\cyclone_tcp" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS\portable\GCC\ARM_CM4F" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS\include" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS\portable" -I"D:\Projects\ProjectsEclipse\BC32X\MCU" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\CMSIS" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\CMSIS\Include" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\stm32h7xx_hal_driver" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\stm32h7xx_hal_driver\Inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


