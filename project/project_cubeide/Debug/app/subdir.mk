################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/app/example.c \
G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/app/main.c 

OBJS += \
./app/example.o \
./app/main.o 

C_DEPS += \
./app/example.d \
./app/main.d 


# Each subdirectory must supply rules for building sources it contributes
app/example.o: G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/app/example.c app/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_STM32CUBEIDE -c -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_dev/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_per/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/common/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/mini_printf/mini-printf" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/mini_printf/lwprintf" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/ring_buffer/lwrb" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
app/main.o: G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/app/main.c app/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_STM32CUBEIDE -c -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_dev/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_per/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/common/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/mini_printf/mini-printf" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/mini_printf/lwprintf" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/ring_buffer/lwrb" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-app

clean-app:
	-$(RM) ./app/example.cyclo ./app/example.d ./app/example.o ./app/example.su ./app/main.cyclo ./app/main.d ./app/main.o ./app/main.su

.PHONY: clean-app

