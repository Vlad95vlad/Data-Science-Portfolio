################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Cyclone_TCP/cyclone_tcp/http/http_client.c \
../Cyclone_TCP/cyclone_tcp/http/http_client_auth.c \
../Cyclone_TCP/cyclone_tcp/http/http_client_misc.c \
../Cyclone_TCP/cyclone_tcp/http/http_client_transport.c \
../Cyclone_TCP/cyclone_tcp/http/http_common.c \
../Cyclone_TCP/cyclone_tcp/http/http_server.c \
../Cyclone_TCP/cyclone_tcp/http/http_server_auth.c \
../Cyclone_TCP/cyclone_tcp/http/http_server_misc.c \
../Cyclone_TCP/cyclone_tcp/http/mime.c \
../Cyclone_TCP/cyclone_tcp/http/ssi.c 

OBJS += \
./Cyclone_TCP/cyclone_tcp/http/http_client.o \
./Cyclone_TCP/cyclone_tcp/http/http_client_auth.o \
./Cyclone_TCP/cyclone_tcp/http/http_client_misc.o \
./Cyclone_TCP/cyclone_tcp/http/http_client_transport.o \
./Cyclone_TCP/cyclone_tcp/http/http_common.o \
./Cyclone_TCP/cyclone_tcp/http/http_server.o \
./Cyclone_TCP/cyclone_tcp/http/http_server_auth.o \
./Cyclone_TCP/cyclone_tcp/http/http_server_misc.o \
./Cyclone_TCP/cyclone_tcp/http/mime.o \
./Cyclone_TCP/cyclone_tcp/http/ssi.o 

C_DEPS += \
./Cyclone_TCP/cyclone_tcp/http/http_client.d \
./Cyclone_TCP/cyclone_tcp/http/http_client_auth.d \
./Cyclone_TCP/cyclone_tcp/http/http_client_misc.d \
./Cyclone_TCP/cyclone_tcp/http/http_client_transport.d \
./Cyclone_TCP/cyclone_tcp/http/http_common.d \
./Cyclone_TCP/cyclone_tcp/http/http_server.d \
./Cyclone_TCP/cyclone_tcp/http/http_server_auth.d \
./Cyclone_TCP/cyclone_tcp/http/http_server_misc.d \
./Cyclone_TCP/cyclone_tcp/http/mime.d \
./Cyclone_TCP/cyclone_tcp/http/ssi.d 


# Each subdirectory must supply rules for building sources it contributes
Cyclone_TCP/cyclone_tcp/http/%.o: ../Cyclone_TCP/cyclone_tcp/http/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DUSE_HAL_DRIVER -DINCLUDE_TCP_TERMINAL -DGPL_LICENSE_TERMS_ACCEPTED -DSTM32H753xx -I"D:\Projects\ProjectsEclipse\BC32X" -I"D:\Projects\ProjectsEclipse\BC32X\OthLibs" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\common" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\cyclone_crypto" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\cyclone_ssl" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\cyclone_tcp" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS\portable\GCC\ARM_CM4F" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS\include" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS\portable" -I"D:\Projects\ProjectsEclipse\BC32X\MCU" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\CMSIS" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\CMSIS\Include" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\stm32h7xx_hal_driver" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\stm32h7xx_hal_driver\Inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


