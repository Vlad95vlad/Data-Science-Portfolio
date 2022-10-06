################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Cyclone_TCP/cyclone_crypto/cipher/aes.c \
../Cyclone_TCP/cyclone_crypto/cipher/aria.c \
../Cyclone_TCP/cyclone_crypto/cipher/blowfish.c \
../Cyclone_TCP/cyclone_crypto/cipher/camellia.c \
../Cyclone_TCP/cyclone_crypto/cipher/chacha.c \
../Cyclone_TCP/cyclone_crypto/cipher/des.c \
../Cyclone_TCP/cyclone_crypto/cipher/des3.c \
../Cyclone_TCP/cyclone_crypto/cipher/idea.c \
../Cyclone_TCP/cyclone_crypto/cipher/present.c \
../Cyclone_TCP/cyclone_crypto/cipher/rc2.c \
../Cyclone_TCP/cyclone_crypto/cipher/rc4.c \
../Cyclone_TCP/cyclone_crypto/cipher/rc6.c \
../Cyclone_TCP/cyclone_crypto/cipher/salsa20.c \
../Cyclone_TCP/cyclone_crypto/cipher/seed.c \
../Cyclone_TCP/cyclone_crypto/cipher/trivium.c 

OBJS += \
./Cyclone_TCP/cyclone_crypto/cipher/aes.o \
./Cyclone_TCP/cyclone_crypto/cipher/aria.o \
./Cyclone_TCP/cyclone_crypto/cipher/blowfish.o \
./Cyclone_TCP/cyclone_crypto/cipher/camellia.o \
./Cyclone_TCP/cyclone_crypto/cipher/chacha.o \
./Cyclone_TCP/cyclone_crypto/cipher/des.o \
./Cyclone_TCP/cyclone_crypto/cipher/des3.o \
./Cyclone_TCP/cyclone_crypto/cipher/idea.o \
./Cyclone_TCP/cyclone_crypto/cipher/present.o \
./Cyclone_TCP/cyclone_crypto/cipher/rc2.o \
./Cyclone_TCP/cyclone_crypto/cipher/rc4.o \
./Cyclone_TCP/cyclone_crypto/cipher/rc6.o \
./Cyclone_TCP/cyclone_crypto/cipher/salsa20.o \
./Cyclone_TCP/cyclone_crypto/cipher/seed.o \
./Cyclone_TCP/cyclone_crypto/cipher/trivium.o 

C_DEPS += \
./Cyclone_TCP/cyclone_crypto/cipher/aes.d \
./Cyclone_TCP/cyclone_crypto/cipher/aria.d \
./Cyclone_TCP/cyclone_crypto/cipher/blowfish.d \
./Cyclone_TCP/cyclone_crypto/cipher/camellia.d \
./Cyclone_TCP/cyclone_crypto/cipher/chacha.d \
./Cyclone_TCP/cyclone_crypto/cipher/des.d \
./Cyclone_TCP/cyclone_crypto/cipher/des3.d \
./Cyclone_TCP/cyclone_crypto/cipher/idea.d \
./Cyclone_TCP/cyclone_crypto/cipher/present.d \
./Cyclone_TCP/cyclone_crypto/cipher/rc2.d \
./Cyclone_TCP/cyclone_crypto/cipher/rc4.d \
./Cyclone_TCP/cyclone_crypto/cipher/rc6.d \
./Cyclone_TCP/cyclone_crypto/cipher/salsa20.d \
./Cyclone_TCP/cyclone_crypto/cipher/seed.d \
./Cyclone_TCP/cyclone_crypto/cipher/trivium.d 


# Each subdirectory must supply rules for building sources it contributes
Cyclone_TCP/cyclone_crypto/cipher/%.o: ../Cyclone_TCP/cyclone_crypto/cipher/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DUSE_HAL_DRIVER -DINCLUDE_TCP_TERMINAL -DGPL_LICENSE_TERMS_ACCEPTED -DSTM32H753xx -I"D:\Projects\ProjectsEclipse\BC32X" -I"D:\Projects\ProjectsEclipse\BC32X\OthLibs" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\common" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\cyclone_crypto" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\cyclone_ssl" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\cyclone_tcp" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS\portable\GCC\ARM_CM4F" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS\include" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS\portable" -I"D:\Projects\ProjectsEclipse\BC32X\MCU" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\CMSIS" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\CMSIS\Include" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\stm32h7xx_hal_driver" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\stm32h7xx_hal_driver\Inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


