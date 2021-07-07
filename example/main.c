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
#include <stdlib.h>
#include <string.h>

#include "hy_uart.h"
#include "hy_timer.h"
#include "hy_log.h"
#include "hy_module.h"

#define ALONE_DEBUG 1

typedef struct {
    void    *uart_handle;
    void    *timer_handle;
} _main_context_t;

static void _timer_cb(void *args)
{
    LOGD("----haha \n");
}

static _main_context_t *_module_create(void)
{
    _main_context_t *context = malloc(sizeof(*context));
    if (!context) {
        LOGE("malloc faild \n");
        return NULL;
    }
    memset(context, '\0', sizeof(*context));

    HyUartConfig_t uart_config;
    uart_config.num     = DEBUG_UART_NUM;
    uart_config.rate    = 115200;

    HyTimerConfig_t timer_config;
    timer_config.num    = HY_TIMER_2;
    timer_config.us     = 1000;
    timer_config.flag   = HY_TIMER_ENABLE;
    timer_config.config_save.timer_cb   = _timer_cb;
    timer_config.config_save.args       = context;

    // note: 增加或删除要同步到module_destroy_t中
    module_create_t module[] = {
        {"debug uart",  context->uart_handle,  &uart_config,   (create_t)HyUartDebugCreate,     HyUartDebugDestroy},
        {"timer",       context->timer_handle, &timer_config,  (create_t)HyTimerCreate,         HyTimerDestroy},
    };

    RUN_CREATE(module);

    return context;
}

static void _module_destroy(_main_context_t *context)
{
    // note: 增加或删除要同步到module_create_t中
    module_destroy_t module[] = {
        {"debug uart",  context->uart_handle,   HyUartDebugDestroy},
        {"timer",       context->timer_handle,  HyTimerDestroy},
    };

    RUN_DESTROY(module);
}

int main(int argc, char const* argv[])
{
    _main_context_t *context = _module_create();
    if (!context) {
        LOGE("_module_create faild \n");
        return -1;
    }

    while (1) {

    }

    _module_destroy(context);

    return 0;
}
