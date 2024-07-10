#include<stdio.h>
#include"ohos_init.h"
#include"hal_iot_uart.h"
#include"mqtt-serve.h"
#include"message.h"




void go_go_go (void)
{
printf("**********************************hello*************************\r\n");
iotda_init(void);
message_go();
printf("finish\r\n");
}

SYS_RUN(go_go_go);