/**
 *
 * Release under GPLv-3.0.
 * 
 * @file    hy_adc.h
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    17/08 2021 18:52
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        17/08 2021      create the file
 * 
 *     last modified: 17/08 2021 18:52
 */
#ifndef __LIBHY_MCU_INCLUDE_HY_ADC_H_
#define __LIBHY_MCU_INCLUDE_HY_ADC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "hy_utils/hy_type.h"

typedef struct {
    void (*adc_cb)(hy_u32_t val, void *args);
    void *args;
} HyAdcConfigSave_t;

typedef struct {
    HyAdcConfigSave_t config_save;
} HyAdcConfig_t;

void *HyAdcCreate(HyAdcConfig_t *adc_config);
void HyAdcDestroy(void **handle);

void HyAdcStart(void *handle);
void HyAdcStop(void *handle);

#ifdef __cplusplus
}
#endif

#endif

