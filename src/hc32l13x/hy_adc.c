/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    hy_adc.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    17/08 2021 18:53
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        17/08 2021      create the file
 * 
 *     last modified: 17/08 2021 18:53
 */
#include <stdio.h>

#include "hy_adc.h"
#include "hy_gpio.h"

#include "adc.h"
#include "bgr.h"
#include "gpio.h"

#include "hy_utils/hy_mem.h"
#include "hy_utils/hy_string.h"
#include "hy_utils/hy_assert.h"
#include "hy_utils/hy_type.h"
#include "hy_utils/hy_log.h"

#define ALONE_DEBUG 1

typedef struct {
    HyAdcConfigSave_t config_save;
} _adc_context_t;

static _adc_context_t *context_arr[1] = {0};

 ///< ADC 中断服务程序
void Adc_IRQHandler(void)
{    
    if(TRUE == Adc_GetIrqStatus(AdcMskIrqSgl)) {
        Adc_ClrIrqStatus(AdcMskIrqSgl);       ///< 清除中断标志位

        hy_u32_t ret = Adc_GetSglResult();   ///< 获取采样值
        LOGE("%08x \n", ret);

        _adc_context_t *context = context_arr[0];
        HyAdcConfigSave_t *config_save = &context->config_save;
        if (config_save->adc_cb) {
            config_save->adc_cb(ret, config_save->args);
        }

        Adc_SGL_Stop();                       ///< ADC 单次转换停止
    }
}

///< ADC模块 初始化
void App_AdcInit(void)
{
    stc_adc_cfg_t              stcAdcCfg;

    DDL_ZERO_STRUCT(stcAdcCfg);
    
    ///< 开启ADC/BGR 外设时钟
    Sysctrl_SetPeripheralGate(SysctrlPeripheralAdcBgr, TRUE); 
    
    Bgr_BgrEnable();        ///< 开启BGR
    
    ///< ADC 初始化配置
    stcAdcCfg.enAdcMode         = AdcSglMode;               ///<采样模式-单次
    stcAdcCfg.enAdcClkDiv       = AdcMskClkDiv1;            ///<采样分频-1
    stcAdcCfg.enAdcSampCycleSel = AdcMskSampCycle12Clk;     ///<采样周期数-12
    stcAdcCfg.enAdcRefVolSel    = AdcMskRefVolSelInBgr2p5;  ///<参考电压选择-内部2.5V
    stcAdcCfg.enAdcOpBuf        = AdcMskBufDisable;         ///<OP BUF配置-关
    stcAdcCfg.enInRef           = AdcMskInRefEnable;        ///<内部参考电压使能-开
    stcAdcCfg.enAdcAlign        = AdcAlignRight;            ///<转换结果对齐方式-右
    Adc_Init(&stcAdcCfg);
}

///< ADC 单次扫描模式 配置
void App_AdcSglCfg(void)
{
    ///< ADC 采样通道配置
    Adc_CfgSglChannel(AdcExInputCH0);
    
    ///< ADC 中断使能
    Adc_EnableIrq();
    EnableNvic(ADC_IRQn, IrqLevel3, TRUE);
}

static void _adc_init()
{
    ///< 开启 GPIO外设时钟
    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);

    Gpio_SetAnalogMode(GpioPortB, GpioPin7);        //PA00 (AIN0)

    App_AdcInit();
    App_AdcSglCfg();
}

void HyAdcStart(void *handle)
{
    HY_ASSERT_NULL_RET(!handle);
    _adc_context_t *context = handle;

    ///< 启动单次转换采样
    Adc_SGL_Start();
}

void HyAdcStop(void *handle)
{
    HY_ASSERT_NULL_RET(!handle);
    _adc_context_t *context = handle;

}

void HyAdcDestroy(void **handle)
{

}

void *HyAdcCreate(HyAdcConfig_t *adc_config)
{
    LOGT("%s:%d \n", __func__, __LINE__);
    HY_ASSERT_NULL_RET_VAL(!adc_config, NULL);

    _adc_context_t *context = NULL;

    do {
        context = (_adc_context_t *)HY_MALLOC_BREAK(sizeof(*context));

        HY_MEMCPY(&context->config_save, &adc_config->config_save);

        _adc_init();

        context_arr[0] = context;

        return context;
    } while (0);

    return NULL;
}

