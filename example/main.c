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

#include "config.h"

#include "hy_system.h"
#include "hy_uart.h"
#include "hy_time.h"

#include "hy_utils/hy_log.h"
#include "hy_utils/hy_module.h"
#include "hy_utils/hy_mem.h"

#define ALONE_DEBUG 1

typedef struct {
    void    *system_handle;
    void    *uart_handle;
    void    *log_handle;
    void    *time_handle;
} _main_context_t;

static void _sys_tick_cb(void *args)
{
#if 1
    static int cnt = 0;
    if (cnt++ == 1000) {
        cnt = 0;
        LOGD("--------tick\n");
    }
#endif
}


static void _time_cb(void *args)
{
#if 0
    static int cnt = 0;
    if (cnt++ == 1000) {
        cnt = 0;
        LOGD("--time\n");
    }
#endif
}

static void _module_destroy(_main_context_t **context_pp)
{
    _main_context_t *context = *context_pp;

    // note: 增加或删除要同步到module_create_t中
    module_destroy_t module[] = {
        {"system",      &context->system_handle,    HySystemDestroy},
        {"debug uart",  &context->uart_handle,      HyUartDebugDestroy},
        {"log",         &context->log_handle,       HyLogDestroy},
        {"time",        &context->time_handle,      HyTimeDestroy},
    };

    RUN_DESTROY(module);

    HY_FREE(context_pp);
}

static _main_context_t *_module_create(void)
{
    _main_context_t *context = HY_MALLOC_RET_VAL(sizeof(*context), NULL);

    HySystemConfig_t system_config;
    system_config.config_save.sys_tick_cb   = _sys_tick_cb;
    system_config.config_save.args          = context;

    HyUartConfig_t uart_config;
    uart_config.num                     = DEBUG_UART_NUM;
    uart_config.rate                    = 115200;

    HyLogConfig_t log_config;
    log_config.buf_len                  = 256;
    log_config.level                    = HY_LOG_LEVEL_TRACE;
    log_config.config_file              = NULL;

    HyTimeConfig_t time_config;
    time_config.num                     = HY_TIME_2;
    time_config.us                      = 1000;
    time_config.flag                    = HY_TIME_ENABLE;
    time_config.config_save.time_cb     = _time_cb;
    time_config.config_save.args        = context;

    // note: 增加或删除要同步到module_destroy_t中
    module_create_t module[] = {
        {"system",      &context->system_handle,    &system_config,     (create_t)HySystemCreate,       HySystemDestroy},
        {"debug uart",  &context->uart_handle,      &uart_config,       (create_t)HyUartDebugCreate,    HyUartDebugDestroy},
        {"log",         &context->log_handle,       &log_config,        (create_t)HyLogCreate,          HyLogDestroy},
        {"time",        &context->time_handle,      &time_config,       (create_t)HyTimeCreate,         HyTimeDestroy},
    };

    RUN_CREATE(module);

    return context;
}

int main(int argc, char const* argv[])
{
    _main_context_t *context = _module_create();
    if (!context) {
        LOGE("_module_create faild \n");
        return -1;
    }

    LOGI("version: %s, date: %s, time: %s \n", VERSION, __DATE__, __TIME__);

    while (1) {
#ifdef USE_SYSTICK_DELAY
        HySystemDelayS(1);
        LOGD("delay 1s\n");
#endif
    }

    _module_destroy(&context);

    return 0;
}

