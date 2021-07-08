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
#include "hy_log.h"

#include "misc.h"

#define ALONE_DEBUG 1
#define SYSTEM_TICK_1MS_FACTOR (1000)   // 产生中断1ms
// #define SYSTEM_TICK_1MS_FACTOR (100)    // 产生中断10ms

typedef struct {
    HySystemConfigSave_t config_save;
} _system_context_t;

static _system_context_t *context = NULL;

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

    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    /* SystTick configuration: an interrupt every 10ms */
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

void HySystemDestroy(void *handle)
{
    if (handle) {
        free(handle);
    }
}

