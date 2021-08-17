/**
 *
 * Release under GPLv-3.0.
 * 
 * @file    hy_time.h
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
#ifndef __LIBHY_MCU_INCLUDE_HY_TIME_H_
#define __LIBHY_MCU_INCLUDE_HY_TIME_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

typedef enum {
    HY_TIME_0,
    HY_TIME_1,
    HY_TIME_2,
    HY_TIME_3,
    HY_TIME_4,
    HY_TIME_5,
    HY_TIME_6,
    HY_TIME_7,
    HY_TIME_8,

    HY_TIME_SYSTICK,

    HY_TIME_MAX,
} HyTimeNum_t;

typedef enum {
    HY_TIME_DISABLE,
    HY_TIME_ENABLE,
} HytimeFlag_t;

typedef struct {
    void (*time_cb)(void *args);
    void *args;
} HyTimeConfigSave_t;

typedef struct {
    HyTimeNum_t    num;
    uint32_t        us;
    HytimeFlag_t   flag;

    HyTimeConfigSave_t config_save;
} HyTimeConfig_t;

void *HyTimeCreate(HyTimeConfig_t *time_config);
void HyTimeDestroy(void **handle);

void HyTimeEnable(void *handle);
void HyTimeDisable(void *handle);

#ifdef __cplusplus
}
#endif

#endif

