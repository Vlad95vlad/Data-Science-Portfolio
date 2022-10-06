################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Cyclone_TCP/cyclone_crypto/encoding/asn1.c \
../Cyclone_TCP/cyclone_crypto/encoding/base64.c \
../Cyclone_TCP/cyclone_crypto/encoding/base64url.c \
../Cyclone_TCP/cyclone_crypto/encoding/oid.c \
../Cyclone_TCP/cyclone_crypto/encoding/radix64.c 

OBJS += \
./Cyclone_TCP/cyclone_crypto/encoding/asn1.o \
./Cyclone_TCP/cyclone_crypto/encoding/base64.o \
./Cyclone_TCP/cyclone_crypto/encoding/base64url.o \
./Cyclone_TCP/cyclone_crypto/encoding/oid.o \
./Cyclone_TCP/cyclone_crypto/encoding/radix64.o 

C_DEPS += \
./Cyclone_TCP/cyclone_crypto/encoding/asn1.d \
./Cyclone_TCP/cyclone_crypto/encoding/base64.d \
./Cyclone_TCP/cyclone_crypto/encoding/base64url.d \
./Cyclone_TCP/cyclone_crypto/encoding/oid.d \
./Cyclone_TCP/cyclone_crypto/encoding/radix64.d 


# Each subdirectory must supply rules for building sources it contributes
Cyclone_TCP/cyclone_crypto/encoding/%.o: ../Cyclone_TCP/cyclone_crypto/encoding/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DUSE_HAL_DRIVER -DINCLUDE_TCP_TERMINAL -DGPL_LICENSE_TERMS_ACCEPTED -DSTM32H753xx -I"D:\Projects\ProjectsEclipse\BC32X" -I"D:\Projects\ProjectsEclipse\BC32X\OthLibs" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\common" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\cyclone_crypto" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\cyclone_ssl" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\cyclone_tcp" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS\portable\GCC\ARM_CM4F" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS\include" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS\portable" -I"D:\Projects\ProjectsEclipse\BC32X\MCU" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\CMSIS" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\CMSIS\Include" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\stm32h7xx_hal_driver" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\stm32h7xx_hal_driver\Inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


