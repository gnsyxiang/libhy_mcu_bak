/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    hy_time.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    06/07 2021 18:57
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        06/07 2021      create the file
 * 
 *     last modified: 06/07 2021 18:57
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hy_time.h"

#include "at32f4xx_rcc.h"

#include "hy_utils/hy_mem.h"
#include "hy_utils/hy_string.h"
#include "hy_utils/hy_log.h"
#include "hy_utils/hy_assert.h"

#define ALONE_DEBUG 1

typedef struct {
    HyTimeNum_t num;

    HyTimeConfigSave_t config_save;
} _time_context_t;

static _time_context_t *context_array[HY_TIME_MAX] = {NULL};

static void _init_time_rcc(HyTimeNum_t num)
{
    if (num == HY_TIME_2) {
        RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_TMR2, ENABLE);
    }
}

static void _init_time_func(HyTimeNum_t num, uint16_t us, int flag)
{
    TMR_Type* time[] = {
        NULL, TMR1, TMR2, TMR3, TMR4, TMR5, TMR6, TMR7, TMR8
    };
    TMR_TimeBaseInitType  config;
    TMR_TimeBaseStructInit(&config);

#ifdef SYSCLK_FREQ_200MHz
    config.TMR_DIV           = 200 - 1;      // 1us
#endif
#ifdef SYSCLK_FREQ_240MHz
    config.TMR_DIV           = 240 - 1;      // 1us
#endif
    // config.TMR_DIV           = 2400 - 1;     // 10us
    // config.TMR_DIV           = 24000 - 1;    // 100us
    config.TMR_Period        = us;
    config.TMR_ClockDivision = TMR_CKD_DIV1;
    config.TMR_CounterMode   = TMR_CounterDIR_Up;
    config.TMR_RepetitionCounter = 0;

    TMR_TimeBaseInit(time[num], &config);

    TMR_Cmd(time[num], (FunctionalState)flag);
}

static void _init_time_interrupt(HyTimeNum_t num, int flag)
{
    if (num == HY_TIME_2) {
        NVIC_InitType config;

        config.NVIC_IRQChannel                      = TMR2_GLOBAL_IRQn;
        config.NVIC_IRQChannelPreemptionPriority    = 0;
        config.NVIC_IRQChannelSubPriority           = 0;
        config.NVIC_IRQChannelCmd                   = (FunctionalState)flag;
        NVIC_Init(&config);

        TMR_INTConfig(TMR2, TMR_INT_Overflow, ENABLE);
    }
}

static void _time_irq_handler(HyTimeNum_t num)
{
    if (context_array[num]) {
        TMR_Type* time[] = {
            NULL, TMR1, TMR2, TMR3, TMR4, TMR5, TMR6, TMR7, TMR8
        };
        HyTimeConfigSave_t *time_config = &context_array[num]->config_save;

        if (TMR_GetINTStatus(time[num], TMR_INT_Overflow) == SET)  {
            TMR_ClearITPendingBit(time[num], TMR_INT_Overflow);
            if (time_config->time_cb) {
                time_config->time_cb(time_config->args);
            }
        }
    }
}

void TMR2_GLOBAL_IRQHandler(void)
{
    _time_irq_handler(HY_TIME_2);
}

static void _time_control_com(void *handle, int flag)
{
    _time_context_t *context = handle;
    TMR_Type* time[] = {
        NULL, TMR1, TMR2, TMR3, TMR4, TMR5, TMR6, TMR7, TMR8
    };

    if (flag) {
        TMR_Cmd(time[context->num], ENABLE);
    } else {
        TMR_Cmd(time[context->num], DISABLE);
    }
}

void HyTimeEnable(void *handle)
{
    HY_ASSERT_NULL_RET(!handle);

    _time_control_com(handle, 1);
}

void HyTimeDisable(void *handle)
{
    HY_ASSERT_NULL_RET(!handle);

    _time_control_com(handle, 0);
}

void HyTimeDestroy(void **handle)
{
    if (handle && *handle) {
        _time_context_t *context = *handle;

        context_array[context->num] = NULL;

        HY_FREE(handle);
    }
}

void *HyTimeCreate(HyTimeConfig_t *time_config)
{
    HY_ASSERT_NULL_RET_VAL(!time_config, NULL);

    _time_context_t *context = NULL;

    do {
        context = HY_MALLOC_BREAK(sizeof(*context));

        context->num                        = time_config->num;
        context_array[time_config->num]    = context;

        HY_MEMCPY(&context->config_save, &time_config->config_save);

        _init_time_rcc(time_config->num);
        _init_time_func(time_config->num, time_config->us, time_config->flag);
        _init_time_interrupt(time_config->num, time_config->flag);

        return context;
    } while (0);

    HyTimeDestroy((void **)&context);

    return NULL;
}

