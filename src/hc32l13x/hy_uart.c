/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    hy_uart.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    17/08 2021 17:25
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        17/08 2021      create the file
 * 
 *     last modified: 17/08 2021 17:25
 */
#include <stdio.h>

#include "hy_uart.h"

#include "hy_utils/hy_log.h"

#define ALONE_DEBUG 1

int HyUartSendByte(void *handle, char byte)
{
    return 0;
}

int HyUartSendBuf(void *handle, void *buf, size_t len)
{
    return 0;
}

void HyUartDestroy(void **handle)
{

}

void *HyUartCreate(HyUartConfig_t *uart_config)
{
    return NULL;
}

#ifdef DEBUG_UART

void HyUartDebugDestroy(void **handle)
{

}

void *HyUartDebugCreate(HyUartConfig_t *uart_config)
{
    return NULL;
}

#endif
