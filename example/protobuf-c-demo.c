/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    protobuf-c-demo.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    04/08 2021 20:51
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        04/08 2021      create the file
 * 
 *     last modified: 04/08 2021 20:51
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

#include "address_book.pb-c.h"

#include "hy_system.h"
#include "hy_uart.h"
#include "hy_timer.h"

#include "hy_utils/hy_log.h"
#include "hy_utils/hy_module.h"
#include "hy_utils/hy_mem.h"

#define ALONE_DEBUG 1

typedef struct {
    void    *system_handle;
    void    *uart_handle;
    void    *log_handle;
    void    *timer_handle;
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


static void _timer_cb(void *args)
{
#if 0
    static int cnt = 0;
    if (cnt++ == 1000) {
        cnt = 0;
        LOGD("--timer\n");
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
        {"timer",       &context->timer_handle,     HyTimerDestroy},
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

    HyTimerConfig_t timer_config;
    timer_config.num                    = HY_TIMER_2;
    timer_config.us                     = 1000;
    timer_config.flag                   = HY_TIMER_ENABLE;
    timer_config.config_save.timer_cb   = _timer_cb;
    timer_config.config_save.args       = context;

    // note: 增加或删除要同步到module_destroy_t中
    module_create_t module[] = {
        {"system",      &context->system_handle,    &system_config,     (create_t)HySystemCreate,       HySystemDestroy},
        {"debug uart",  &context->uart_handle,      &uart_config,       (create_t)HyUartDebugCreate,    HyUartDebugDestroy},
        {"log",         &context->log_handle,       &log_config,        (create_t)HyLogCreate,          HyLogDestroy},
        {"timer",       &context->timer_handle,     &timer_config,      (create_t)HyTimerCreate,        HyTimerDestroy},
    };

    RUN_CREATE(module);

    return context;
}

static int32_t _do_pack(uint8_t *buf)
{
    Tutorial__Person__PhoneNumber *phone_number = HY_MALLOC_RET_VAL(sizeof(*phone_number), -1);
    tutorial__person__phone_number__init(phone_number);

    phone_number->type = TUTORIAL__PERSON__PHONE_TYPE__HOME;
    phone_number->number = "110";

    Tutorial__Person *person = HY_MALLOC_RET_VAL(sizeof(*person), -1);
    tutorial__person__init(person);

    person->id = 1;
    person->name = "haha";
    person->email = "haha@110.com";
    person->n_phones = 1;
    person->phones = &phone_number;

    Tutorial__Addressbook address_book = TUTORIAL__ADDRESSBOOK__INIT;

    address_book.n_people = 1;
    address_book.people = &person;

    int32_t len = tutorial__addressbook__pack(&address_book, buf);

    HY_FREE(&phone_number);

    HY_FREE(&person);

    return len;
}

static int32_t _do_unpack(const uint8_t *buf, size_t len)
{
    Tutorial__Addressbook *address_book = tutorial__addressbook__unpack(NULL, len, buf);
    if (!address_book) {
        LOGE("user__unpack failed\n");
        return -1;
    }

    for (size_t i = 0; i < address_book->n_people; ++i) {
        Tutorial__Person *people = address_book->people[i];

        LOGD("id: %ld, name: %s, email: %s \n",
                people->id, people->name, people->email);
    }

    tutorial__addressbook__free_unpacked(address_book, NULL);

    return 0;
}

int main(int argc, char const* argv[])
{
    _main_context_t *context = _module_create();
    if (!context) {
        LOGE("_module_create faild \n");
        return -1;
    }

    LOGI("version: %s, date: %s, time: %s \n", VERSION, __DATE__, __TIME__);

    uint8_t buf[1024] = {0};
    int32_t len = 0;

    len = _do_pack(buf);
    LOGD("len: %ld \n", len);

    _do_unpack(buf, len);

    while (1) {
#ifdef USE_SYSTICK_DELAY
        HySystemDelayS(1);
        LOGD("delay 1s\n");
#endif
    }

    _module_destroy(&context);

    return 0;
}

