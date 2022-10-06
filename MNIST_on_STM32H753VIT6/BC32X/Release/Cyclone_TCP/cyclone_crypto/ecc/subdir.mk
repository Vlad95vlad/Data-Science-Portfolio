################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Cyclone_TCP/cyclone_crypto/ecc/curve25519.c \
../Cyclone_TCP/cyclone_crypto/ecc/curve448.c \
../Cyclone_TCP/cyclone_crypto/ecc/ec.c \
../Cyclone_TCP/cyclone_crypto/ecc/ec_curves.c \
../Cyclone_TCP/cyclone_crypto/ecc/ecdh.c \
../Cyclone_TCP/cyclone_crypto/ecc/ecdsa.c \
../Cyclone_TCP/cyclone_crypto/ecc/ed25519.c \
../Cyclone_TCP/cyclone_crypto/ecc/ed448.c \
../Cyclone_TCP/cyclone_crypto/ecc/eddsa.c \
../Cyclone_TCP/cyclone_crypto/ecc/x25519.c \
../Cyclone_TCP/cyclone_crypto/ecc/x448.c 

OBJS += \
./Cyclone_TCP/cyclone_crypto/ecc/curve25519.o \
./Cyclone_TCP/cyclone_crypto/ecc/curve448.o \
./Cyclone_TCP/cyclone_crypto/ecc/ec.o \
./Cyclone_TCP/cyclone_crypto/ecc/ec_curves.o \
./Cyclone_TCP/cyclone_crypto/ecc/ecdh.o \
./Cyclone_TCP/cyclone_crypto/ecc/ecdsa.o \
./Cyclone_TCP/cyclone_crypto/ecc/ed25519.o \
./Cyclone_TCP/cyclone_crypto/ecc/ed448.o \
./Cyclone_TCP/cyclone_crypto/ecc/eddsa.o \
./Cyclone_TCP/cyclone_crypto/ecc/x25519.o \
./Cyclone_TCP/cyclone_crypto/ecc/x448.o 

C_DEPS += \
./Cyclone_TCP/cyclone_crypto/ecc/curve25519.d \
./Cyclone_TCP/cyclone_crypto/ecc/curve448.d \
./Cyclone_TCP/cyclone_crypto/ecc/ec.d \
./Cyclone_TCP/cyclone_crypto/ecc/ec_curves.d \
./Cyclone_TCP/cyclone_crypto/ecc/ecdh.d \
./Cyclone_TCP/cyclone_crypto/ecc/ecdsa.d \
./Cyclone_TCP/cyclone_crypto/ecc/ed25519.d \
./Cyclone_TCP/cyclone_crypto/ecc/ed448.d \
./Cyclone_TCP/cyclone_crypto/ecc/eddsa.d \
./Cyclone_TCP/cyclone_crypto/ecc/x25519.d \
./Cyclone_TCP/cyclone_crypto/ecc/x448.d 


# Each subdirectory must supply rules for building sources it contributes
Cyclone_TCP/cyclone_crypto/ecc/%.o: ../Cyclone_TCP/cyclone_crypto/ecc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DUSE_HAL_DRIVER -DINCLUDE_TCP_TERMINAL -DGPL_LICENSE_TERMS_ACCEPTED -DSTM32H753xx -I"D:\Projects\ProjectsEclipse\BC32X" -I"D:\Projects\ProjectsEclipse\BC32X\OthLibs" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\common" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\cyclone_crypto" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\cyclone_ssl" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\cyclone_tcp" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS\portable\GCC\ARM_CM4F" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS\include" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS\portable" -I"D:\Projects\ProjectsEclipse\BC32X\MCU" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\CMSIS" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\CMSIS\Include" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\stm32h7xx_hal_driver" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\stm32h7xx_hal_driver\Inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


