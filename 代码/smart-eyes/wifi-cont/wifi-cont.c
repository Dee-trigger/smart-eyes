#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "ohos_init.h"
#include "cmsis_os2.h"


#include "hal_bsp_wifi.h"
#include "wifi_device.h"


osThreadId_t Task_ID; // 任务1设置为低优先级任务
#define TASK_STACK_SIZE (1024 * 10)
#define WIFI_SSID "oneplus"
#define WIFI_PAWD "66666666"



void wifi_Task()
{
    WifiErrorCode result;
    WiFi_connectHotspots(WIFI_SSID, WIFI_PAWD);
   while (1) {
        sleep(1); // 1 s
    } 
}
 void network_wifi_sta()
{
    printf("Enter network_wifi_sta!\r\n");


    osThreadAttr_t options;
    options.name = "cont_wifi";
    options.attr_bits = 0;
    options.cb_mem = NULL;
    options.cb_size = 0;
    options.stack_mem = NULL;
    options.stack_size = TASK_STACK_SIZE;
    options.priority = osPriorityNormal; 
    
    Task_ID = osThreadNew((osThreadFunc_t)wifi_Task, NULL, &options);
     if (Task_ID != NULL) {
     printf("ID = %d, Create wifi is OK!\r\n", Task_ID);
   }
   
}
//SYS_RUN(network_wifi_sta);