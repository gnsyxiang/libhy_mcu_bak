/**
 *
 * Release under GPLv-3.0.
 * 
 * @file    hy_timer.h
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    06/07 2021 18:51
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        06/07 2021      create the file
 * 
 *     last modified: 06/07 2021 18:51
 */
#ifndef __LIBHY_MCU_INCLUDE_HY_TIMER_H_
#define __LIBHY_MCU_INCLUDE_HY_TIMER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

typedef enum {
    HY_TIMER_0,
    HY_TIMER_1,
    HY_TIMER_2,
    HY_TIMER_3,
    HY_TIMER_4,
    HY_TIMER_5,
    HY_TIMER_6,
    HY_TIMER_7,
    HY_TIMER_8,

    HY_TIMER_SYSTICK,

    HY_TIMER_MAX,
} HyTimerNum_t;

typedef enum {
    HY_TIMER_DISABLE,
    HY_TIMER_ENABLE,
} HytimerFlag_t;

typedef struct {
    void (*timer_cb)(void *args);
    void *args;
} HyTimerConfigSave_t;

typedef struct {
    HyTimerNum_t    num;
    uint32_t        us;
    HytimerFlag_t   flag;

    HyTimerConfigSave_t config_save;
} HyTimerConfig_t;

void *HyTimerCreate(HyTimerConfig_t *timer_config);
void HyTimerDestroy(void **handle);

void HyTimerEnable(void *handle);
void HyTimerDisable(void *handle);

#ifdef __cplusplus
}
#endif

#endif

