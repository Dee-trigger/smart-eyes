
char tem_char[3];
char get_tem()
{
    return tem_char;
}
void uart_task1()
{   int len=0;
     char uartReadBuff[100] = {0};
     unsigned tem_int=0;
     
     bool val;
      
    char cmd_data='AA A5 03 01 04 55';//测温命令
      while (1) {
        val=0;
        IoTGpioGetInputVal(9, &val);
        // 通过UART1 发送数据 Send data through UART1
        if(val=1){ IoTUartWrite(HI_UART_IDX_1, &cmd_data, 17);IoTGpioSetOutputVal(2, 1);
        IoTPwmStart(3,  100, 100);}
          else{IoTGpioSetOutputVal(2,0);IoTPwmStop(3);}
        // 通过UART1 接收数据 Receive data through UART1
        len = IoTUartRead(HI_UART_IDX_1, uartReadBuff, 32);
        if (len > 0) {
            // 计算体温
            tem_int=(((int)uartReadBuff[16]-48)*256+((int)uartReadBuff[17]-48)*16+((int)uartReadBuff[18]-48));
            tem_char[0]=tem_int/100;
            tem_char[1]=tem_int/10;
            tem_char[2]=tem_int;
            printf("Uart Read Data is:  %s \r\n",  uartReadBuff);
            IoTGpioSetOutputVal(10, 1);
            sleep(1);
            IoTGpioSetOutputVal(10 ,0);
            IoTI2cWrite(1, 0x11,&tem_char, 3);//通过i2c发送到屏幕驱动板

        }
         printf("Uart Read ");
        usleep(1000);
        
        
    }

}
void uart1_go()
{    uart1_init();
    gpio_device();
   IoTPwmStart(3,100, 100);
   IoTPwmStart(2,100, 100);
   IoTPwmStart(1,100, 100);
   IoTPwmStart(0,100, 100);
   printf("pwm_ok");
   
      IoTI2cInit(1, 400000);
     osThreadAttr_t attr;
    

    attr.name = "UartTask";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = 5 * 1024; // 任务栈大小*1024 stack size 5*1024
    attr.priority = osPriorityNormal;

    if (osThreadNew((osThreadFunc_t)uart_task1, NULL, &attr) == NULL) {
        printf("[UartTask] Failed to create uart_task1!\n");
    } 
}
void gpio_device()
{
IoTGpioInit(2);//补光灯
IoTGpioSetDir(2, 1);//输出
IoTGpioInit(9);//毫米波雷达
IoTGpioSetDir(9,0);//输入
IoTGpioInit(10);//喷雾
IoTGpioSetDir(10, 1);//输出

IoTGpioInit(7);//
hi_io_set_func(7,5);
IoTGpioSetDir(7, 1);//配置pwm
IoTPwmInit(0);

IoTGpioInit(8);//
hi_io_set_func(7,5);
IoTGpioSetDir(8, 1);//配置pwm
IoTPwmInit(1);

IoTGpioInit(6);//
hi_io_set_func(6,5);
IoTGpioSetDir(6, 1);//配置pwm
IoTPwmInit(3);

IoTGpioInit(5);//
hi_io_set_func(5,5);
IoTGpioSetDir(5,1);//配置pwm
IoTPwmInit(2);
}