/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    hy_system.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    08/07 2021 08:21
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        08/07 2021      create the file
 * 
 *     last modified: 08/07 2021 08:21
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hy_system.h"

#include "hy_utils/hy_log.h"
#include "hy_utils/hy_mem.h"

#include "misc.h"

#define ALONE_DEBUG 1
#define SYSTEM_TICK_1MS_FACTOR (1000)   // 产生中断1ms
// #define SYSTEM_TICK_1MS_FACTOR (100)    // 产生中断10ms

typedef struct {
    HySystemConfigSave_t config_save;
} _system_context_t;

static _system_context_t *context = NULL;

#ifdef USE_SYSTICK_DELAY

static void _delay_com(uint32_t us)
{
    SysTick->LOAD   = us;
    SysTick->VAL    = 0x00;
    SysTick->CTRL  |= SysTick_CTRL_ENABLE_Msk;

    uint32_t temp;
    do {
        temp = SysTick->CTRL;
    } while ((temp & 0x01) && !(temp & (1 << 16)));

    SysTick->CTRL  &= ~SysTick_CTRL_ENABLE_Msk;
    SysTick->VAL    = 0x00;
}

void HySystemDelayUs(uint32_t us)
{
    uint32_t fac_us = SystemCoreClock / (1000000U);

    _delay_com(us * fac_us);
}

void HySystemDelayMs(uint32_t ms)
{
    #define STEP_DELAY_MS 50
    uint32_t ms_tmp;
    uint32_t fac_ms = SystemCoreClock / (1000U);

    while (ms) {
        if (ms > STEP_DELAY_MS) {
            ms_tmp  = (uint32_t)(STEP_DELAY_MS * fac_ms);
            ms      -= STEP_DELAY_MS;
        } else {
            ms_tmp  = (uint32_t)(ms * fac_ms);
            ms      = 0;
        }

        _delay_com(ms_tmp);
    }
}

void HySystemDelayS(uint32_t s)
{
    for (size_t i = 0; i < s; ++i) {
        HySystemDelayMs(500);
        HySystemDelayMs(500);
    }
}
#endif

void SysTick_Handler(void)
{
    if (context) {
        HySystemConfigSave_t *config_save = &context->config_save;
        if (config_save->sys_tick_cb) {
            config_save->sys_tick_cb(config_save->args);
        }
    }
}

static void _init_system(void)
{
    RCC_ClockType RCC_Clocks;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);

    RCC_GetClocksFreq(&RCC_Clocks);
    SysTick_Config(RCC_Clocks.SYSCLK_Freq / SYSTEM_TICK_1MS_FACTOR);

    NVIC_SetPriority(SysTick_IRQn, 1);
}

void *HySystemCreate(HySystemConfig_t *system_config)
{
    if (!system_config) {
        return NULL;
    }

    do {
        context = malloc(sizeof(*context));
        if (!context) {
            LOGE("malloc faild \n");
            return NULL;
        }
        memset(context, '\0', sizeof(*context));

        memcpy(&context->config_save, &system_config->config_save,
                sizeof(context->config_save));

        _init_system();

        return context;
    } while (0);

    return NULL;
}

void HySystemDestroy(void **handle)
{
    if (handle && *handle) {
        HY_FREE(handle);
    }
}

