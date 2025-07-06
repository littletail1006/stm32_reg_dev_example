################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_per/source/adc.c \
G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_per/source/dma.c \
G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_per/source/i2c.c \
G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_per/source/i2c_io.c \
G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_per/source/tim.c \
G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_per/source/usart.c \
G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_per/source/wdg.c 

OBJS += \
./driver/drv_per/source/adc.o \
./driver/drv_per/source/dma.o \
./driver/drv_per/source/i2c.o \
./driver/drv_per/source/i2c_io.o \
./driver/drv_per/source/tim.o \
./driver/drv_per/source/usart.o \
./driver/drv_per/source/wdg.o 

C_DEPS += \
./driver/drv_per/source/adc.d \
./driver/drv_per/source/dma.d \
./driver/drv_per/source/i2c.d \
./driver/drv_per/source/i2c_io.d \
./driver/drv_per/source/tim.d \
./driver/drv_per/source/usart.d \
./driver/drv_per/source/wdg.d 


# Each subdirectory must supply rules for building sources it contributes
driver/drv_per/source/adc.o: G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_per/source/adc.c driver/drv_per/source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_STM32CUBEIDE -c -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_dev/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_per/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/common/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/mini_printf/mini-printf" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/mini_printf/lwprintf" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/ring_buffer/lwrb" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
driver/drv_per/source/dma.o: G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_per/source/dma.c driver/drv_per/source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_STM32CUBEIDE -c -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_dev/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_per/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/common/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/mini_printf/mini-printf" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/mini_printf/lwprintf" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/ring_buffer/lwrb" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
driver/drv_per/source/i2c.o: G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_per/source/i2c.c driver/drv_per/source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_STM32CUBEIDE -c -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_dev/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_per/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/common/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/mini_printf/mini-printf" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/mini_printf/lwprintf" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/ring_buffer/lwrb" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
driver/drv_per/source/i2c_io.o: G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_per/source/i2c_io.c driver/drv_per/source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_STM32CUBEIDE -c -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_dev/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_per/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/common/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/mini_printf/mini-printf" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/mini_printf/lwprintf" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/ring_buffer/lwrb" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
driver/drv_per/source/tim.o: G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_per/source/tim.c driver/drv_per/source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_STM32CUBEIDE -c -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_dev/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_per/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/common/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/mini_printf/mini-printf" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/mini_printf/lwprintf" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/ring_buffer/lwrb" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
driver/drv_per/source/usart.o: G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_per/source/usart.c driver/drv_per/source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_STM32CUBEIDE -c -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_dev/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_per/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/common/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/mini_printf/mini-printf" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/mini_printf/lwprintf" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/ring_buffer/lwrb" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
driver/drv_per/source/wdg.o: G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_per/source/wdg.c driver/drv_per/source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_STM32CUBEIDE -c -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_dev/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/driver/drv_per/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/common/include" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/mini_printf/mini-printf" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/mini_printf/lwprintf" -I"G:/WorkSpace/workspace_STM32CubeIDE/stm32_project_template/component/ring_buffer/lwrb" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-driver-2f-drv_per-2f-source

clean-driver-2f-drv_per-2f-source:
	-$(RM) ./driver/drv_per/source/adc.cyclo ./driver/drv_per/source/adc.d ./driver/drv_per/source/adc.o ./driver/drv_per/source/adc.su ./driver/drv_per/source/dma.cyclo ./driver/drv_per/source/dma.d ./driver/drv_per/source/dma.o ./driver/drv_per/source/dma.su ./driver/drv_per/source/i2c.cyclo ./driver/drv_per/source/i2c.d ./driver/drv_per/source/i2c.o ./driver/drv_per/source/i2c.su ./driver/drv_per/source/i2c_io.cyclo ./driver/drv_per/source/i2c_io.d ./driver/drv_per/source/i2c_io.o ./driver/drv_per/source/i2c_io.su ./driver/drv_per/source/tim.cyclo ./driver/drv_per/source/tim.d ./driver/drv_per/source/tim.o ./driver/drv_per/source/tim.su ./driver/drv_per/source/usart.cyclo ./driver/drv_per/source/usart.d ./driver/drv_per/source/usart.o ./driver/drv_per/source/usart.su ./driver/drv_per/source/wdg.cyclo ./driver/drv_per/source/wdg.d ./driver/drv_per/source/wdg.o ./driver/drv_per/source/wdg.su

.PHONY: clean-driver-2f-drv_per-2f-source

