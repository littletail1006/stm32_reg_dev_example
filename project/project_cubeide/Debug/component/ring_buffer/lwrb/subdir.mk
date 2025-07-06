################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/ring_buffer/lwrb/lwrb.c \
G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/ring_buffer/lwrb/lwrb_ex.c 

OBJS += \
./component/ring_buffer/lwrb/lwrb.o \
./component/ring_buffer/lwrb/lwrb_ex.o 

C_DEPS += \
./component/ring_buffer/lwrb/lwrb.d \
./component/ring_buffer/lwrb/lwrb_ex.d 


# Each subdirectory must supply rules for building sources it contributes
component/ring_buffer/lwrb/lwrb.o: G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/ring_buffer/lwrb/lwrb.c component/ring_buffer/lwrb/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_STM32CUBEIDE -c -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_dev/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_per/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/common/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/mini_printf/mini-printf" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/mini_printf/lwprintf" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/ring_buffer/lwrb" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
component/ring_buffer/lwrb/lwrb_ex.o: G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/ring_buffer/lwrb/lwrb_ex.c component/ring_buffer/lwrb/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_STM32CUBEIDE -c -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_dev/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_per/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/common/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/mini_printf/mini-printf" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/mini_printf/lwprintf" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/ring_buffer/lwrb" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-component-2f-ring_buffer-2f-lwrb

clean-component-2f-ring_buffer-2f-lwrb:
	-$(RM) ./component/ring_buffer/lwrb/lwrb.cyclo ./component/ring_buffer/lwrb/lwrb.d ./component/ring_buffer/lwrb/lwrb.o ./component/ring_buffer/lwrb/lwrb.su ./component/ring_buffer/lwrb/lwrb_ex.cyclo ./component/ring_buffer/lwrb/lwrb_ex.d ./component/ring_buffer/lwrb/lwrb_ex.o ./component/ring_buffer/lwrb/lwrb_ex.su

.PHONY: clean-component-2f-ring_buffer-2f-lwrb

