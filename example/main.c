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

static void _read_cb(char byte, void *args)
{

}

int main(int argc, char const* argv[])
{
    HyUartConfig_t uart_config;
    uart_config.num = HY_UART_1;
    uart_config.rate = 115200;
    uart_config.config_save.read_cb = _read_cb;
    uart_config.config_save.args = NULL;

    void *handle = HyUartCreate(&uart_config);
    if (!handle) {
        return -1;
    }

    while (1) {

    }

    HyUartDestroy(handle);

    return 0;
}
