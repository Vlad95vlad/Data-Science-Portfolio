################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Cyclone_TCP/cyclone_tcp/ipv6/icmpv6.c \
../Cyclone_TCP/cyclone_tcp/ipv6/ipv6.c \
../Cyclone_TCP/cyclone_tcp/ipv6/ipv6_frag.c \
../Cyclone_TCP/cyclone_tcp/ipv6/ipv6_misc.c \
../Cyclone_TCP/cyclone_tcp/ipv6/ipv6_pmtu.c \
../Cyclone_TCP/cyclone_tcp/ipv6/ipv6_routing.c \
../Cyclone_TCP/cyclone_tcp/ipv6/mld.c \
../Cyclone_TCP/cyclone_tcp/ipv6/ndp.c \
../Cyclone_TCP/cyclone_tcp/ipv6/ndp_cache.c \
../Cyclone_TCP/cyclone_tcp/ipv6/ndp_misc.c \
../Cyclone_TCP/cyclone_tcp/ipv6/ndp_router_adv.c \
../Cyclone_TCP/cyclone_tcp/ipv6/ndp_router_adv_misc.c \
../Cyclone_TCP/cyclone_tcp/ipv6/slaac.c \
../Cyclone_TCP/cyclone_tcp/ipv6/slaac_misc.c 

OBJS += \
./Cyclone_TCP/cyclone_tcp/ipv6/icmpv6.o \
./Cyclone_TCP/cyclone_tcp/ipv6/ipv6.o \
./Cyclone_TCP/cyclone_tcp/ipv6/ipv6_frag.o \
./Cyclone_TCP/cyclone_tcp/ipv6/ipv6_misc.o \
./Cyclone_TCP/cyclone_tcp/ipv6/ipv6_pmtu.o \
./Cyclone_TCP/cyclone_tcp/ipv6/ipv6_routing.o \
./Cyclone_TCP/cyclone_tcp/ipv6/mld.o \
./Cyclone_TCP/cyclone_tcp/ipv6/ndp.o \
./Cyclone_TCP/cyclone_tcp/ipv6/ndp_cache.o \
./Cyclone_TCP/cyclone_tcp/ipv6/ndp_misc.o \
./Cyclone_TCP/cyclone_tcp/ipv6/ndp_router_adv.o \
./Cyclone_TCP/cyclone_tcp/ipv6/ndp_router_adv_misc.o \
./Cyclone_TCP/cyclone_tcp/ipv6/slaac.o \
./Cyclone_TCP/cyclone_tcp/ipv6/slaac_misc.o 

C_DEPS += \
./Cyclone_TCP/cyclone_tcp/ipv6/icmpv6.d \
./Cyclone_TCP/cyclone_tcp/ipv6/ipv6.d \
./Cyclone_TCP/cyclone_tcp/ipv6/ipv6_frag.d \
./Cyclone_TCP/cyclone_tcp/ipv6/ipv6_misc.d \
./Cyclone_TCP/cyclone_tcp/ipv6/ipv6_pmtu.d \
./Cyclone_TCP/cyclone_tcp/ipv6/ipv6_routing.d \
./Cyclone_TCP/cyclone_tcp/ipv6/mld.d \
./Cyclone_TCP/cyclone_tcp/ipv6/ndp.d \
./Cyclone_TCP/cyclone_tcp/ipv6/ndp_cache.d \
./Cyclone_TCP/cyclone_tcp/ipv6/ndp_misc.d \
./Cyclone_TCP/cyclone_tcp/ipv6/ndp_router_adv.d \
./Cyclone_TCP/cyclone_tcp/ipv6/ndp_router_adv_misc.d \
./Cyclone_TCP/cyclone_tcp/ipv6/slaac.d \
./Cyclone_TCP/cyclone_tcp/ipv6/slaac_misc.d 


# Each subdirectory must supply rules for building sources it contributes
Cyclone_TCP/cyclone_tcp/ipv6/%.o: ../Cyclone_TCP/cyclone_tcp/ipv6/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DUSE_HAL_DRIVER -DINCLUDE_TCP_TERMINAL -DGPL_LICENSE_TERMS_ACCEPTED -DSTM32H753xx -I"D:\Projects\ProjectsEclipse\BC32X" -I"D:\Projects\ProjectsEclipse\BC32X\OthLibs" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\common" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\cyclone_crypto" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\cyclone_ssl" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\cyclone_tcp" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS\portable\GCC\ARM_CM4F" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS\include" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS\portable" -I"D:\Projects\ProjectsEclipse\BC32X\MCU" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\CMSIS" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\CMSIS\Include" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\stm32h7xx_hal_driver" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\stm32h7xx_hal_driver\Inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


