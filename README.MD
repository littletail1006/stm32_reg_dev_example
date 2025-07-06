# STM32寄存器开发入门教程示例

## 简介

> **【STM32寄存器入门教程】** 
>
> **@Keil+STM32CubeIDE双环境** 
>
> **@第一人称带入边学边讲 通俗易懂** 
>
> **@潜移默化的带入养成良好的代码编程风格的习惯** 
>
> **@引导你如何学习 如何思考 解决问题** 
>
> **我相信屏幕前的你 日后一定可以成为真正的强者、高手**
>
> **祝大家永远都有解决任何事物的能力**

## 示例

```apl
    example_01_gpio_led();                //GPIO实验1   点亮LED 了解IO口配置及输出控制
    example_02_gpio_key();     			  //GPIO实验2   检测KEY 了解IO口配置及输入检测
    example_03_gpio_remap();   			  //GPIO实验3   重映射IO 了解IO口复用重映射
    example_04_gpio_bitband(); 		      //GPIO实验4   位带操作IO 了解IO口位带操作
    example_05_exti_key();      		  //EXTI实验    按键中断 了解外部中断
    example_06_irq_priority();  		  //IRQ实验     配置中断优先级 了解中断优先级配置
    example_07_delay();         		  //SYSTICK实验 实现精确延时函数 了解延时实现方式
    example_08_usart_polltx_isrrx();      //USART实验1  实现查询式发送中断式接收
    example_09_usart_printf();            //USART实验2  printf重定向到串口
    example_10_usart_ringbuffer();        //USART实验3  环形缓冲区+IDEL中断
    example_11_dma_mem2mem_poll();        //DMA实验1    存储器到存储器模式(查询式)
    example_12_dma_mem2mem_interrupt();   //DMA实验2    存储器到存储器模式(中断式)
    example_13_usart_dma_tx_mem2per();    //USART实验4  串口DMA发送(存储器到外设)
    example_14_usart_dma_rx_per2mem();    //USART实验5  串口DMA接收(外设到存储器)
    example_15_usart_dma_idle_ringbuf();  //USART实验6  串口DMA收发+IDLE+环形缓存
    example_16_hw_i2c();                  //I2C实验1    硬件实现作为主机模式下的收发
    example_17_sw_i2c();                  //I2C实验2    IO模拟I2C实现主机模式的收发
    example_18_oled();                    //I2C实验3    OLED屏幕显示
    example_19_tim_timing();              //TIM实验1    定时
    example_20_tim_pwm();                 //TIM实验2    PWM输出
    example_21_tim_oc();                  //TIM实验3    Output Compare输出比较
    example_22_tim_ic();                  //TIM实验4    Input Capture 输入捕获
    example_23_adc_poll_01();             //ADC实验1    单路规则通道独立不扫描连续转换(查询式)
    example_24_adc_poll_02();             //ADC实验2    多路规则通道(需开启扫描加dma)
    example_25_adc_poll_03();             //ADC实验3    注入通道(使用方式和规则一样)
    example_26_adc_int();                 //ADC实验4    中断式
    example_27_wdg();                     //WDG实验     独立和窗口看门狗
    example_28_rtc();                     //RTC实验     日期 时间戳(秒计数)和闹钟
```



## 文件目录结构

```plaintext
stm32_reg_dev_example/
├── app/                  # 应用程序目录
│   ├── main.c             # 主函数
│   ├── example.c          # 例子
├── common/               # 通用文件目录
│   ├── include/           # 头文件
│   ├── source/            # 源文件
├── component/            # 组件
│   ├── mini_printf/       # printf
│   ├── ring_buffer/       # ringbuf
├── driver/               # 驱动目录
│   ├── drv_dev/           # 外围设备驱动目录
│   ├── drv_per/           # 基础外设驱动目录
└── project/              # 工程目录
│   ├── project_cubeide/   # cubeide工程
│   ├── project_keil/      # keil工程
│   ├── project_vscode/    # vscode eide工程
└── reference/  	      # 文档目录
```
