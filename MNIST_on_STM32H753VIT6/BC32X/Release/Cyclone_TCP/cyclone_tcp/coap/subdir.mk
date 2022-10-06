################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Cyclone_TCP/cyclone_tcp/coap/coap_client.c \
../Cyclone_TCP/cyclone_tcp/coap/coap_client_block.c \
../Cyclone_TCP/cyclone_tcp/coap/coap_client_misc.c \
../Cyclone_TCP/cyclone_tcp/coap/coap_client_observe.c \
../Cyclone_TCP/cyclone_tcp/coap/coap_client_request.c \
../Cyclone_TCP/cyclone_tcp/coap/coap_client_transport.c \
../Cyclone_TCP/cyclone_tcp/coap/coap_debug.c \
../Cyclone_TCP/cyclone_tcp/coap/coap_message.c \
../Cyclone_TCP/cyclone_tcp/coap/coap_option.c \
../Cyclone_TCP/cyclone_tcp/coap/coap_server.c \
../Cyclone_TCP/cyclone_tcp/coap/coap_server_misc.c \
../Cyclone_TCP/cyclone_tcp/coap/coap_server_request.c \
../Cyclone_TCP/cyclone_tcp/coap/coap_server_transport.c 

OBJS += \
./Cyclone_TCP/cyclone_tcp/coap/coap_client.o \
./Cyclone_TCP/cyclone_tcp/coap/coap_client_block.o \
./Cyclone_TCP/cyclone_tcp/coap/coap_client_misc.o \
./Cyclone_TCP/cyclone_tcp/coap/coap_client_observe.o \
./Cyclone_TCP/cyclone_tcp/coap/coap_client_request.o \
./Cyclone_TCP/cyclone_tcp/coap/coap_client_transport.o \
./Cyclone_TCP/cyclone_tcp/coap/coap_debug.o \
./Cyclone_TCP/cyclone_tcp/coap/coap_message.o \
./Cyclone_TCP/cyclone_tcp/coap/coap_option.o \
./Cyclone_TCP/cyclone_tcp/coap/coap_server.o \
./Cyclone_TCP/cyclone_tcp/coap/coap_server_misc.o \
./Cyclone_TCP/cyclone_tcp/coap/coap_server_request.o \
./Cyclone_TCP/cyclone_tcp/coap/coap_server_transport.o 

C_DEPS += \
./Cyclone_TCP/cyclone_tcp/coap/coap_client.d \
./Cyclone_TCP/cyclone_tcp/coap/coap_client_block.d \
./Cyclone_TCP/cyclone_tcp/coap/coap_client_misc.d \
./Cyclone_TCP/cyclone_tcp/coap/coap_client_observe.d \
./Cyclone_TCP/cyclone_tcp/coap/coap_client_request.d \
./Cyclone_TCP/cyclone_tcp/coap/coap_client_transport.d \
./Cyclone_TCP/cyclone_tcp/coap/coap_debug.d \
./Cyclone_TCP/cyclone_tcp/coap/coap_message.d \
./Cyclone_TCP/cyclone_tcp/coap/coap_option.d \
./Cyclone_TCP/cyclone_tcp/coap/coap_server.d \
./Cyclone_TCP/cyclone_tcp/coap/coap_server_misc.d \
./Cyclone_TCP/cyclone_tcp/coap/coap_server_request.d \
./Cyclone_TCP/cyclone_tcp/coap/coap_server_transport.d 


# Each subdirectory must supply rules for building sources it contributes
Cyclone_TCP/cyclone_tcp/coap/%.o: ../Cyclone_TCP/cyclone_tcp/coap/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DUSE_HAL_DRIVER -DINCLUDE_TCP_TERMINAL -DGPL_LICENSE_TERMS_ACCEPTED -DSTM32H753xx -I"D:\Projects\ProjectsEclipse\BC32X" -I"D:\Projects\ProjectsEclipse\BC32X\OthLibs" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\common" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\cyclone_crypto" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\cyclone_ssl" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\cyclone_tcp" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS\portable\GCC\ARM_CM4F" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS\include" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS\portable" -I"D:\Projects\ProjectsEclipse\BC32X\MCU" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\CMSIS" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\CMSIS\Include" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\stm32h7xx_hal_driver" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\stm32h7xx_hal_driver\Inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


