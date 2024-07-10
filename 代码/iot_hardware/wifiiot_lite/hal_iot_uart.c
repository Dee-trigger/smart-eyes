/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "hal_iot_pwm.h"
#include "ohos_init.h"
#include "cmsis_os2.h"
#include "iot_gpio.h"
#include "iot_uart.h"
#include "hi_uart.h"
#include "iot_watchdog.h"
#include "iot_errno.h"
#include "hal_iot_uart.h"
#include  "hal_iot_i2c.h"

unsigned int IoTUartInit(unsigned int id, const IotUartAttribute *param)
{
    hi_uart_attribute attr = {0};
    hi_uart_extra_attr extraAttr = {0};

    if (NULL == param) {
        return IOT_FAILURE;
    }

    attr.baud_rate = param->baudRate;
    attr.data_bits = param->dataBits;
    attr.pad = param->pad;
    attr.parity = param->parity;
    attr.stop_bits = param->stopBits;

    if (IOT_UART_BLOCK_STATE_NONE_BLOCK == param->rxBlock) {
        extraAttr.rx_block = HI_UART_BLOCK_STATE_NONE_BLOCK;
    } else {
        extraAttr.rx_block = HI_UART_BLOCK_STATE_BLOCK;
    }

    if (IOT_UART_BLOCK_STATE_NONE_BLOCK == param->txBlock) {
        extraAttr.tx_block = HI_UART_BLOCK_STATE_NONE_BLOCK;
    } else {
        extraAttr.tx_block = HI_UART_BLOCK_STATE_BLOCK;
    }

    return hi_uart_init((hi_uart_idx)id, &attr, &extraAttr);
}

int IoTUartRead(unsigned int id, unsigned char *data, unsigned int dataLen)
{
    return hi_uart_read((hi_uart_idx)id, data, dataLen);
}

int IoTUartWrite(unsigned int id, const unsigned char *data, unsigned int dataLen)
{
    return hi_uart_write((hi_uart_idx)id, data, dataLen);
}

unsigned int IoTUartDeinit(unsigned int id)
{
    return hi_uart_deinit((hi_uart_idx)id);
}

unsigned int IoTUartSetFlowCtrl(unsigned int id, IotFlowCtrl flowCtrl)
{
    return hi_uart_set_flow_ctrl((hi_uart_idx)id, (hi_flow_ctrl)flowCtrl);
}

void uart1_init()
{
IoTGpioInit(0);
    // 设置GPIO0的管脚复用关系为UART1_TX Set the pin reuse relationship of GPIO0 to UART1_ TX
hi_io_set_func(0,2);

IoTGpioInit(1);
    // 设置GPIO1的管脚复用关系为UART1_RX Set the pin reuse relationship of GPIO1 to UART1_ RX
hi_io_set_func(1,2);

IotUartAttribute uart;
uart.baudRate=38400;
uart.dataBits=8;
uart.parity=0;
uart.stopBits=1;

IoTUartInit(HI_UART_IDX_1,&uart);
}