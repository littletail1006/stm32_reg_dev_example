################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_dev/source/key.c \
G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_dev/source/led.c \
G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_dev/source/oled.c 

OBJS += \
./driver/drv_dev/source/key.o \
./driver/drv_dev/source/led.o \
./driver/drv_dev/source/oled.o 

C_DEPS += \
./driver/drv_dev/source/key.d \
./driver/drv_dev/source/led.d \
./driver/drv_dev/source/oled.d 


# Each subdirectory must supply rules for building sources it contributes
driver/drv_dev/source/key.o: G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_dev/source/key.c driver/drv_dev/source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_STM32CUBEIDE -c -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_dev/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_per/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/common/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/mini_printf/mini-printf" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/mini_printf/lwprintf" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/ring_buffer/lwrb" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
driver/drv_dev/source/led.o: G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_dev/source/led.c driver/drv_dev/source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_STM32CUBEIDE -c -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_dev/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_per/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/common/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/mini_printf/mini-printf" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/mini_printf/lwprintf" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/ring_buffer/lwrb" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
driver/drv_dev/source/oled.o: G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_dev/source/oled.c driver/drv_dev/source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_STM32CUBEIDE -c -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_dev/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_per/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/common/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/mini_printf/mini-printf" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/mini_printf/lwprintf" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/ring_buffer/lwrb" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-driver-2f-drv_dev-2f-source

clean-driver-2f-drv_dev-2f-source:
	-$(RM) ./driver/drv_dev/source/key.cyclo ./driver/drv_dev/source/key.d ./driver/drv_dev/source/key.o ./driver/drv_dev/source/key.su ./driver/drv_dev/source/led.cyclo ./driver/drv_dev/source/led.d ./driver/drv_dev/source/led.o ./driver/drv_dev/source/led.su ./driver/drv_dev/source/oled.cyclo ./driver/drv_dev/source/oled.d ./driver/drv_dev/source/oled.o ./driver/drv_dev/source/oled.su

.PHONY: clean-driver-2f-drv_dev-2f-source

