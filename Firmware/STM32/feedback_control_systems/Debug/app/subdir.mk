################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../app/app_sm.c \
../app/control.c \
../app/digital_filter.c \
../app/hw.c 

OBJS += \
./app/app_sm.o \
./app/control.o \
./app/digital_filter.o \
./app/hw.o 

C_DEPS += \
./app/app_sm.d \
./app/control.d \
./app/digital_filter.d \
./app/hw.d 


# Each subdirectory must supply rules for building sources it contributes
app/%.o app/%.su app/%.cyclo: ../app/%.c app/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/pedrobt/github_projects/scr_workspace/FeedbackControlSystems_FinalProject/Firmware/STM32/feedback_control_systems/app" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-app

clean-app:
	-$(RM) ./app/app_sm.cyclo ./app/app_sm.d ./app/app_sm.o ./app/app_sm.su ./app/control.cyclo ./app/control.d ./app/control.o ./app/control.su ./app/digital_filter.cyclo ./app/digital_filter.d ./app/digital_filter.o ./app/digital_filter.su ./app/hw.cyclo ./app/hw.d ./app/hw.o ./app/hw.su

.PHONY: clean-app

