################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Cyclone_TCP/cyclone_crypto/hash/blake2b.c \
../Cyclone_TCP/cyclone_crypto/hash/blake2b160.c \
../Cyclone_TCP/cyclone_crypto/hash/blake2b256.c \
../Cyclone_TCP/cyclone_crypto/hash/blake2b384.c \
../Cyclone_TCP/cyclone_crypto/hash/blake2b512.c \
../Cyclone_TCP/cyclone_crypto/hash/blake2s.c \
../Cyclone_TCP/cyclone_crypto/hash/blake2s128.c \
../Cyclone_TCP/cyclone_crypto/hash/blake2s160.c \
../Cyclone_TCP/cyclone_crypto/hash/blake2s224.c \
../Cyclone_TCP/cyclone_crypto/hash/blake2s256.c \
../Cyclone_TCP/cyclone_crypto/hash/md2.c \
../Cyclone_TCP/cyclone_crypto/hash/md4.c \
../Cyclone_TCP/cyclone_crypto/hash/md5.c \
../Cyclone_TCP/cyclone_crypto/hash/ripemd128.c \
../Cyclone_TCP/cyclone_crypto/hash/ripemd160.c \
../Cyclone_TCP/cyclone_crypto/hash/sha1.c \
../Cyclone_TCP/cyclone_crypto/hash/sha224.c \
../Cyclone_TCP/cyclone_crypto/hash/sha256.c \
../Cyclone_TCP/cyclone_crypto/hash/sha384.c \
../Cyclone_TCP/cyclone_crypto/hash/sha3_224.c \
../Cyclone_TCP/cyclone_crypto/hash/sha3_256.c \
../Cyclone_TCP/cyclone_crypto/hash/sha3_384.c \
../Cyclone_TCP/cyclone_crypto/hash/sha3_512.c \
../Cyclone_TCP/cyclone_crypto/hash/sha512.c \
../Cyclone_TCP/cyclone_crypto/hash/sha512_224.c \
../Cyclone_TCP/cyclone_crypto/hash/sha512_256.c \
../Cyclone_TCP/cyclone_crypto/hash/tiger.c \
../Cyclone_TCP/cyclone_crypto/hash/whirlpool.c 

OBJS += \
./Cyclone_TCP/cyclone_crypto/hash/blake2b.o \
./Cyclone_TCP/cyclone_crypto/hash/blake2b160.o \
./Cyclone_TCP/cyclone_crypto/hash/blake2b256.o \
./Cyclone_TCP/cyclone_crypto/hash/blake2b384.o \
./Cyclone_TCP/cyclone_crypto/hash/blake2b512.o \
./Cyclone_TCP/cyclone_crypto/hash/blake2s.o \
./Cyclone_TCP/cyclone_crypto/hash/blake2s128.o \
./Cyclone_TCP/cyclone_crypto/hash/blake2s160.o \
./Cyclone_TCP/cyclone_crypto/hash/blake2s224.o \
./Cyclone_TCP/cyclone_crypto/hash/blake2s256.o \
./Cyclone_TCP/cyclone_crypto/hash/md2.o \
./Cyclone_TCP/cyclone_crypto/hash/md4.o \
./Cyclone_TCP/cyclone_crypto/hash/md5.o \
./Cyclone_TCP/cyclone_crypto/hash/ripemd128.o \
./Cyclone_TCP/cyclone_crypto/hash/ripemd160.o \
./Cyclone_TCP/cyclone_crypto/hash/sha1.o \
./Cyclone_TCP/cyclone_crypto/hash/sha224.o \
./Cyclone_TCP/cyclone_crypto/hash/sha256.o \
./Cyclone_TCP/cyclone_crypto/hash/sha384.o \
./Cyclone_TCP/cyclone_crypto/hash/sha3_224.o \
./Cyclone_TCP/cyclone_crypto/hash/sha3_256.o \
./Cyclone_TCP/cyclone_crypto/hash/sha3_384.o \
./Cyclone_TCP/cyclone_crypto/hash/sha3_512.o \
./Cyclone_TCP/cyclone_crypto/hash/sha512.o \
./Cyclone_TCP/cyclone_crypto/hash/sha512_224.o \
./Cyclone_TCP/cyclone_crypto/hash/sha512_256.o \
./Cyclone_TCP/cyclone_crypto/hash/tiger.o \
./Cyclone_TCP/cyclone_crypto/hash/whirlpool.o 

C_DEPS += \
./Cyclone_TCP/cyclone_crypto/hash/blake2b.d \
./Cyclone_TCP/cyclone_crypto/hash/blake2b160.d \
./Cyclone_TCP/cyclone_crypto/hash/blake2b256.d \
./Cyclone_TCP/cyclone_crypto/hash/blake2b384.d \
./Cyclone_TCP/cyclone_crypto/hash/blake2b512.d \
./Cyclone_TCP/cyclone_crypto/hash/blake2s.d \
./Cyclone_TCP/cyclone_crypto/hash/blake2s128.d \
./Cyclone_TCP/cyclone_crypto/hash/blake2s160.d \
./Cyclone_TCP/cyclone_crypto/hash/blake2s224.d \
./Cyclone_TCP/cyclone_crypto/hash/blake2s256.d \
./Cyclone_TCP/cyclone_crypto/hash/md2.d \
./Cyclone_TCP/cyclone_crypto/hash/md4.d \
./Cyclone_TCP/cyclone_crypto/hash/md5.d \
./Cyclone_TCP/cyclone_crypto/hash/ripemd128.d \
./Cyclone_TCP/cyclone_crypto/hash/ripemd160.d \
./Cyclone_TCP/cyclone_crypto/hash/sha1.d \
./Cyclone_TCP/cyclone_crypto/hash/sha224.d \
./Cyclone_TCP/cyclone_crypto/hash/sha256.d \
./Cyclone_TCP/cyclone_crypto/hash/sha384.d \
./Cyclone_TCP/cyclone_crypto/hash/sha3_224.d \
./Cyclone_TCP/cyclone_crypto/hash/sha3_256.d \
./Cyclone_TCP/cyclone_crypto/hash/sha3_384.d \
./Cyclone_TCP/cyclone_crypto/hash/sha3_512.d \
./Cyclone_TCP/cyclone_crypto/hash/sha512.d \
./Cyclone_TCP/cyclone_crypto/hash/sha512_224.d \
./Cyclone_TCP/cyclone_crypto/hash/sha512_256.d \
./Cyclone_TCP/cyclone_crypto/hash/tiger.d \
./Cyclone_TCP/cyclone_crypto/hash/whirlpool.d 


# Each subdirectory must supply rules for building sources it contributes
Cyclone_TCP/cyclone_crypto/hash/%.o: ../Cyclone_TCP/cyclone_crypto/hash/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DUSE_HAL_DRIVER -DINCLUDE_TCP_TERMINAL -DGPL_LICENSE_TERMS_ACCEPTED -DSTM32H753xx -I"D:\Projects\ProjectsEclipse\BC32X" -I"D:\Projects\ProjectsEclipse\BC32X\OthLibs" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\common" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\cyclone_crypto" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\cyclone_ssl" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\cyclone_tcp" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS\portable\GCC\ARM_CM4F" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS\include" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS\portable" -I"D:\Projects\ProjectsEclipse\BC32X\MCU" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\CMSIS" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\CMSIS\Include" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\stm32h7xx_hal_driver" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\stm32h7xx_hal_driver\Inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


