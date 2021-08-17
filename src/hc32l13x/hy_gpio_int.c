/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    hy_gpio_int.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    17/08 2021 19:09
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        17/08 2021      create the file
 * 
 *     last modified: 17/08 2021 19:09
 */
#include <stdio.h>

#include "hy_gpio_int.h"

#include "gpio.h"

#include "hy_utils/hy_type.h"
#include "hy_utils/hy_mem.h"
#include "hy_utils/hy_string.h"
#include "hy_utils/hy_assert.h"
#include "hy_utils/hy_log.h"

#define ALONE_DEBUG 1

typedef struct {
    HyIntConfigSave_t config_save;

    hy_u8_t pin_num;
} _int_context_t;

static _int_context_t *context_arr[HY_GPIO_PIN_MAX] = {0};

void PortA_IRQHandler(void)
{
    _int_context_t *context = context_arr[HY_GPIO_PIN_8];

    if (TRUE == Gpio_GetIrqStatus(GpioPortA, GpioPin8)) {
        Gpio_ClearIrq(GpioPortA, GpioPin8);

        HyIntConfigSave_t *config_save = &context->config_save;
        if (config_save->int_cb) {
            config_save->int_cb(config_save->args);
        }
    }
}

static void _int_irq(HyIntConfig_t *int_config)
{
    en_gpio_port_t group[HY_GPIO_GROUP_MAX] = {
        GpioPortA, GpioPortB, GpioPortC, GpioPortD
    };

    en_gpio_pin_t pin[HY_GPIO_PIN_MAX] = {
        GpioPin0,   GpioPin1,   GpioPin2,   GpioPin3,
        GpioPin4,   GpioPin5,   GpioPin6,   GpioPin7,
        GpioPin8,   GpioPin9,   GpioPin10,  GpioPin11,
        GpioPin12,  GpioPin13,  GpioPin14,  GpioPin15,
    };

    IRQn_Type enIrq[] = {
        PORTA_IRQn, PORTB_IRQn, PORTC_IRQn, PORTD_IRQn,
    };


    en_gpio_irqtype_t enType[] = {
        GpioIrqLow, GpioIrqHigh, GpioIrqRising, GpioIrqFalling
    };

    HyGpio_t *gpio = &int_config->gpio;
    Gpio_EnableIrq(group[gpio->group], pin[gpio->pin], enType[int_config->trigger_mode]);
    EnableNvic(enIrq[gpio->group], IrqLevel3, TRUE);
}

void HyIntDestroy(void **handle)
{
    LOGT("%s:%d \n", __func__, __LINE__);
    HY_ASSERT_NULL_RET(!handle || !*handle);

    HY_FREE(handle);
}

void *HyIntCreate(HyIntConfig_t *int_config)
{
    LOGT("%s:%d \n", __func__, __LINE__);
    HY_ASSERT_NULL_RET_VAL(!int_config, NULL);

    _int_context_t *context = NULL;

    do {
        context = (_int_context_t *)HY_MALLOC_BREAK(sizeof(*context));

        HY_MEMCPY(&context->config_save, &int_config->config_save);
        context->pin_num = int_config->gpio.pin;

        HyGpioSetInput(&int_config->gpio);

        _int_irq(int_config);

        context_arr[context->pin_num] = context;

        return context;
    } while (0);

    HyIntDestroy((void **)&context);
    return NULL;
}
