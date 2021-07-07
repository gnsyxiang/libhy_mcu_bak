/**
 *
 * Release under GPLv-3.0.
 * 
 * @file    hy_log.h
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    01/06 2021 14:48
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        01/06 2021      create the file
 * 
 *     last modified: 01/06 2021 14:48
 */
#ifndef __LIBHY_MCU_INCLUDE_HY_LOG_H_
#define __LIBHY_MCU_INCLUDE_HY_LOG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @brief 输出对应的log等级函数
 */
#define LOGF(fmt, ...) printf(fmt, ##__VA_ARGS__)
#define LOGE(fmt, ...) printf(fmt, ##__VA_ARGS__)
#define LOGW(fmt, ...) printf(fmt, ##__VA_ARGS__)
#define LOGI(fmt, ...) printf(fmt, ##__VA_ARGS__)
#define LOGD(fmt, ...) printf(fmt, ##__VA_ARGS__)
#define LOGT(fmt, ...) printf(fmt, ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif

