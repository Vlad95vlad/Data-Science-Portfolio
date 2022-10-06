################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Cyclone_TCP/cyclone_crypto/pkix/pem_export.c \
../Cyclone_TCP/cyclone_crypto/pkix/pem_import.c \
../Cyclone_TCP/cyclone_crypto/pkix/pkcs8_key_format.c \
../Cyclone_TCP/cyclone_crypto/pkix/pkcs8_key_parse.c \
../Cyclone_TCP/cyclone_crypto/pkix/x509_cert_create.c \
../Cyclone_TCP/cyclone_crypto/pkix/x509_cert_parse.c \
../Cyclone_TCP/cyclone_crypto/pkix/x509_cert_validate.c \
../Cyclone_TCP/cyclone_crypto/pkix/x509_common.c \
../Cyclone_TCP/cyclone_crypto/pkix/x509_crl_parse.c \
../Cyclone_TCP/cyclone_crypto/pkix/x509_crl_validate.c \
../Cyclone_TCP/cyclone_crypto/pkix/x509_csr_create.c \
../Cyclone_TCP/cyclone_crypto/pkix/x509_csr_parse.c \
../Cyclone_TCP/cyclone_crypto/pkix/x509_csr_validate.c \
../Cyclone_TCP/cyclone_crypto/pkix/x509_key_format.c \
../Cyclone_TCP/cyclone_crypto/pkix/x509_key_parse.c 

OBJS += \
./Cyclone_TCP/cyclone_crypto/pkix/pem_export.o \
./Cyclone_TCP/cyclone_crypto/pkix/pem_import.o \
./Cyclone_TCP/cyclone_crypto/pkix/pkcs8_key_format.o \
./Cyclone_TCP/cyclone_crypto/pkix/pkcs8_key_parse.o \
./Cyclone_TCP/cyclone_crypto/pkix/x509_cert_create.o \
./Cyclone_TCP/cyclone_crypto/pkix/x509_cert_parse.o \
./Cyclone_TCP/cyclone_crypto/pkix/x509_cert_validate.o \
./Cyclone_TCP/cyclone_crypto/pkix/x509_common.o \
./Cyclone_TCP/cyclone_crypto/pkix/x509_crl_parse.o \
./Cyclone_TCP/cyclone_crypto/pkix/x509_crl_validate.o \
./Cyclone_TCP/cyclone_crypto/pkix/x509_csr_create.o \
./Cyclone_TCP/cyclone_crypto/pkix/x509_csr_parse.o \
./Cyclone_TCP/cyclone_crypto/pkix/x509_csr_validate.o \
./Cyclone_TCP/cyclone_crypto/pkix/x509_key_format.o \
./Cyclone_TCP/cyclone_crypto/pkix/x509_key_parse.o 

C_DEPS += \
./Cyclone_TCP/cyclone_crypto/pkix/pem_export.d \
./Cyclone_TCP/cyclone_crypto/pkix/pem_import.d \
./Cyclone_TCP/cyclone_crypto/pkix/pkcs8_key_format.d \
./Cyclone_TCP/cyclone_crypto/pkix/pkcs8_key_parse.d \
./Cyclone_TCP/cyclone_crypto/pkix/x509_cert_create.d \
./Cyclone_TCP/cyclone_crypto/pkix/x509_cert_parse.d \
./Cyclone_TCP/cyclone_crypto/pkix/x509_cert_validate.d \
./Cyclone_TCP/cyclone_crypto/pkix/x509_common.d \
./Cyclone_TCP/cyclone_crypto/pkix/x509_crl_parse.d \
./Cyclone_TCP/cyclone_crypto/pkix/x509_crl_validate.d \
./Cyclone_TCP/cyclone_crypto/pkix/x509_csr_create.d \
./Cyclone_TCP/cyclone_crypto/pkix/x509_csr_parse.d \
./Cyclone_TCP/cyclone_crypto/pkix/x509_csr_validate.d \
./Cyclone_TCP/cyclone_crypto/pkix/x509_key_format.d \
./Cyclone_TCP/cyclone_crypto/pkix/x509_key_parse.d 


# Each subdirectory must supply rules for building sources it contributes
Cyclone_TCP/cyclone_crypto/pkix/%.o: ../Cyclone_TCP/cyclone_crypto/pkix/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DUSE_HAL_DRIVER -DINCLUDE_TCP_TERMINAL -DGPL_LICENSE_TERMS_ACCEPTED -DSTM32H753xx -I"D:\Projects\ProjectsEclipse\BC32X" -I"D:\Projects\ProjectsEclipse\BC32X\OthLibs" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\common" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\cyclone_crypto" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\cyclone_ssl" -I"D:\Projects\ProjectsEclipse\BC32X\Cyclone_TCP\cyclone_tcp" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS\portable\GCC\ARM_CM4F" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS\include" -I"D:\Projects\ProjectsEclipse\BC32X\FreeRTOS\portable" -I"D:\Projects\ProjectsEclipse\BC32X\MCU" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\CMSIS" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\CMSIS\Include" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\stm32h7xx_hal_driver" -I"D:\Projects\ProjectsEclipse\BC32X\MCU\stm32h7xx_hal_driver\Inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


