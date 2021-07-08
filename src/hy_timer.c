/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    hy_timer.c
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

#include "hy_timer.h"

#include "at32f4xx_rcc.h"

#include "hy_log.h"

#define ALONE_DEBUG 1

typedef struct {
    HyTimerNum_t num;

    HyTimerConfigSave_t config_save;
} _timer_context_t;

static _timer_context_t *context_array[HY_TIMER_MAX] = {NULL};

static void _init_timer_rcc(HyTimerNum_t num)
{
    if (num == HY_TIMER_2) {
        RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_TMR2, ENABLE);
    }
}

static void _init_timer_func(HyTimerNum_t num, uint16_t us, int flag)
{
    TMR_Type* timer[] = {
        NULL, TMR1, TMR2, TMR3, TMR4, TMR5, TMR6, TMR7, TMR8
    };
    TMR_TimerBaseInitType  config;
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

    TMR_TimeBaseInit(timer[num], &config);

    TMR_Cmd(timer[num], (FunctionalState)flag);
}

static void _init_timer_interrupt(HyTimerNum_t num, int flag)
{
    if (num == HY_TIMER_2) {
        NVIC_InitType config;

        config.NVIC_IRQChannel                      = TMR2_GLOBAL_IRQn;
        config.NVIC_IRQChannelPreemptionPriority    = 0;
        config.NVIC_IRQChannelSubPriority           = 0;
        config.NVIC_IRQChannelCmd                   = (FunctionalState)flag;
        NVIC_Init(&config);

        TMR_INTConfig(TMR2, TMR_INT_Overflow, ENABLE);
    }
}

void *HyTimerCreate(HyTimerConfig_t *timer_config)
{
    if (!timer_config) {
        LOGE("the param is NULL \n");
        return NULL;
    }

    _timer_context_t *context = NULL;

    do {
        context = malloc(sizeof(*context));
        if (!context) {
            break;
        }
        memset(context, '\0', sizeof(*context));

        context->num                        = timer_config->num;
        context_array[timer_config->num]    = context;
        memcpy(&context->config_save, &timer_config->config_save,
                sizeof(context->config_save));

        _init_timer_rcc(timer_config->num);
        _init_timer_func(timer_config->num, timer_config->us, timer_config->flag);
        _init_timer_interrupt(timer_config->num, timer_config->flag);

        return context;
    } while (0);

    return NULL;
}

void HyTimerDestroy(void *handle)
{
    if (handle) {
        _timer_context_t *context = handle;

        context_array[context->num] = NULL;
        free(context);
    }
}

static void _timer_irq_handler(HyTimerNum_t num)
{
    if (context_array[num]) {
        TMR_Type* timer[] = {
            NULL, TMR1, TMR2, TMR3, TMR4, TMR5, TMR6, TMR7, TMR8
        };
        HyTimerConfigSave_t *timer_config = &context_array[num]->config_save;

        if (TMR_GetINTStatus(timer[num], TMR_INT_Overflow) == SET)  {
            TMR_ClearITPendingBit(timer[num], TMR_INT_Overflow);
            if (timer_config->timer_cb) {
                timer_config->timer_cb(timer_config->args);
            }
        }
    }
}

void TMR2_GLOBAL_IRQHandler(void)
{
    _timer_irq_handler(HY_TIMER_2);
}

static void _timer_control_com(void *handle, int flag)
{
    _timer_context_t *context = handle;
    TMR_Type* timer[] = {
        NULL, TMR1, TMR2, TMR3, TMR4, TMR5, TMR6, TMR7, TMR8
    };

    if (flag) {
        TMR_Cmd(timer[context->num], ENABLE);
    } else {
        TMR_Cmd(timer[context->num], DISABLE);
    }
}

void HyTimerEnable(void *handle)
{
    if (!handle) {
        LOGE("the param is NULL \n");
        return;
    }

    _timer_control_com(handle, 1);
}

void HyTimerDisable(void *handle)
{
    if (!handle) {
        LOGE("the param is NULL \n");
        return;
    }

    _timer_control_com(handle, 0);
}

