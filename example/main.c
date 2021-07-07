/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    test.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    18/03 2021 20:21
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        18/03 2021      create the file
 * 
 *     last modified: 18/03 2021 20:21
 */
#include <stdio.h>

#include "hy_uart.h"

int main(int argc, char const* argv[])
{
    HyUartConfig_t uart_config;
    uart_config.num     = DEBUG_UART_NUM;
    uart_config.rate    = 115200;

    void *handle = HyUartDebugCreate(&uart_config);
    if (!handle) {
        return -1;
    }

    printf("-----haha\n");

    while (1) {

    }

    HyUartDebugDestroy(handle);

    return 0;
}
