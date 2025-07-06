################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/mini_printf/mini-printf/mini-printf.c 

OBJS += \
./component/mini_printf/mini-printf/mini-printf.o 

C_DEPS += \
./component/mini_printf/mini-printf/mini-printf.d 


# Each subdirectory must supply rules for building sources it contributes
component/mini_printf/mini-printf/mini-printf.o: G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/mini_printf/mini-printf/mini-printf.c component/mini_printf/mini-printf/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_STM32CUBEIDE -c -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_dev/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_per/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/common/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/mini_printf/mini-printf" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/mini_printf/lwprintf" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/ring_buffer/lwrb" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-component-2f-mini_printf-2f-mini-2d-printf

clean-component-2f-mini_printf-2f-mini-2d-printf:
	-$(RM) ./component/mini_printf/mini-printf/mini-printf.cyclo ./component/mini_printf/mini-printf/mini-printf.d ./component/mini_printf/mini-printf/mini-printf.o ./component/mini_printf/mini-printf/mini-printf.su

.PHONY: clean-component-2f-mini_printf-2f-mini-2d-printf

