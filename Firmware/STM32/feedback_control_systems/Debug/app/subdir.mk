################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../app/app_sm.c \
../app/checksum.c \
../app/control.c \
../app/hal_uart.c \
../app/hw.c \
../app/payload_composer.c 

OBJS += \
./app/app_sm.o \
./app/checksum.o \
./app/control.o \
./app/hal_uart.o \
./app/hw.o \
./app/payload_composer.o 

C_DEPS += \
./app/app_sm.d \
./app/checksum.d \
./app/control.d \
./app/hal_uart.d \
./app/hw.d \
./app/payload_composer.d 


# Each subdirectory must supply rules for building sources it contributes
app/%.o app/%.su app/%.cyclo: ../app/%.c app/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/pedrobt/github_projects/scr_workspace/FeedbackControlSystems_FinalProject/Firmware/STM32/feedback_control_systems/app" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-app

clean-app:
	-$(RM) ./app/app_sm.cyclo ./app/app_sm.d ./app/app_sm.o ./app/app_sm.su ./app/checksum.cyclo ./app/checksum.d ./app/checksum.o ./app/checksum.su ./app/control.cyclo ./app/control.d ./app/control.o ./app/control.su ./app/hal_uart.cyclo ./app/hal_uart.d ./app/hal_uart.o ./app/hal_uart.su ./app/hw.cyclo ./app/hw.d ./app/hw.o ./app/hw.su ./app/payload_composer.cyclo ./app/payload_composer.d ./app/payload_composer.o ./app/payload_composer.su

.PHONY: clean-app

