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

#define ALONE_DEBUG 1

#define HyUtilsArrayCnt(array) (int)(sizeof((array)) / sizeof((array)[0]))

typedef struct {
    void    *uart_handle;
    void    *timer_handle;
} _main_context_t;

static void _timer_cb(void *args)
{
    LOGD("----haha \n");
}

typedef void *(*create_t)(void *config);
typedef void (*destroy_t)(void *handle);
typedef struct {
    char        *name;
    void        *handle;
    void        *config;
    create_t    create;
    destroy_t   destroy;
} _module_create_t;

typedef struct {
    char        *name;
    void        *handle;
    destroy_t   destroy;
} _module_destroy_t;

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

    // note: 增加或删除要同步到_module_destroy_t中
    _module_create_t module[] = {
        {"debug uart",  context->uart_handle,  &uart_config,   (create_t)HyUartDebugCreate,     HyUartDebugDestroy},
        {"timer",       context->timer_handle, &timer_config,  (create_t)HyTimerCreate,         HyTimerDestroy},
    };

    int i = 0;
    int len = HyUtilsArrayCnt(module);
    for (i = 0; i < len; ++i) {
        _module_create_t *module_tmp = &module[i];
        module_tmp->handle = module_tmp->create(module_tmp->config);
        if (!module_tmp->handle) {
            LOGE("%s create error \n", module_tmp->name);
            break;
        }
    }

    if (i < len) {
        for (int j = i - 1; j >= 0; j--) {
            _module_create_t *module_tmp = &module[j];
            module_tmp->destroy(module_tmp->handle);
        }
        return NULL;
    }

    return context;
}

static void _module_destroy(_main_context_t *context)
{
    // note: 增加或删除要同步到_module_create_t中
    _module_destroy_t module[] = {
        {"debug uart",  context->uart_handle,   HyUartDebugDestroy},
        {"timer",       context->timer_handle,  HyTimerDestroy},
    };

    for (int i = 0; i < HyUtilsArrayCnt(module); ++i) {
        _module_destroy_t *module_tmp = &module[i];
        module_tmp->destroy(module_tmp->handle);
    }
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
