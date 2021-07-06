/**
 *
 * Release under GPLv-3.0.
 * 
 * @file    hy_uart.h
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    06/07 2021 16:09
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        06/07 2021      create the file
 * 
 *     last modified: 06/07 2021 16:09
 */
#ifndef __LIBHY_MCU_INCLUDE_HY_UART_H_
#define __LIBHY_MCU_INCLUDE_HY_UART_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

typedef enum {
    HY_UART_0,
    HY_UART_1,
    HY_UART_2,
    HY_UART_3,
    HY_UART_4,
    HY_UART_5,

    HY_UART_MAX
} HyUartNum_t;

typedef struct {
    void (*read_cb)(char byte, void *args);
    void *args;
} HyUartConfigSave_t;

typedef struct {
    HyUartNum_t num;
    uint32_t    rate;

    HyUartConfigSave_t config_save;
} HyUartConfig_t;

void *HyUartCreate(HyUartConfig_t *uart_config);
void HyUartDestroy(void *handle);

int HyUartSendByte(void *handle, char byte);
int HyUartSendBuf(void *handle, void *buf, size_t len);

#ifdef __cplusplus
}
#endif

#endif

