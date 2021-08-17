/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    hy_gpio.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    17/08 2021 18:55
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        17/08 2021      create the file
 * 
 *     last modified: 17/08 2021 18:55
 */
#include <stdio.h>

#include "hy_gpio.h"

#include "gpio.h"

#include "hy_utils/hy_type.h"
#include "hy_utils/hy_log.h"

#define ALONE_DEBUG 1

static void _init_PA_pin(HyGpio_t *gpio,
        en_gpio_dir_t dir, HyGpioLevel_t level)
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

    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);

    stc_gpio_cfg_t stcGpioCfg;
    memset(&stcGpioCfg, '\0', sizeof(stcGpioCfg));

    stcGpioCfg.enDir = dir;

    switch (gpio->pin) {
        case HY_GPIO_PIN_6:
            stcGpioCfg.enPu  = GpioPuEnable;
            stcGpioCfg.enPd  = GpioPdDisable;
            break;
        case HY_GPIO_PIN_7:
            stcGpioCfg.enPu  = GpioPuEnable;
            stcGpioCfg.enPd  = GpioPdDisable;
            break;
        case HY_GPIO_PIN_8:
            stcGpioCfg.enPu  = GpioPuEnable;
            stcGpioCfg.enPd  = GpioPdDisable;
            stcGpioCfg.enDrv = GpioDrvL;
            stcGpioCfg.enOD = GpioOdDisable;
            stcGpioCfg.enCtrlMode = GpioAHB;
            break;
        case HY_GPIO_PIN_9:
            stcGpioCfg.enPu  = GpioPuDisable;
            stcGpioCfg.enPd  = GpioPdDisable;
            break;
        case HY_GPIO_PIN_10:
            stcGpioCfg.enPu  = GpioPuDisable;
            stcGpioCfg.enPd  = GpioPdDisable;
            break;
        case HY_GPIO_PIN_11:
            stcGpioCfg.enPu  = GpioPuEnable;
            stcGpioCfg.enPd  = GpioPdDisable;
            break;
        case HY_GPIO_PIN_12:
            stcGpioCfg.enPu  = GpioPuEnable;
            stcGpioCfg.enPd  = GpioPdDisable;
            break;
        default:
            break;
    }
    Gpio_Init(group[gpio->group], pin[gpio->pin], &stcGpioCfg);

    switch (gpio->pin) {
        case HY_GPIO_PIN_9:
            Gpio_SetAfMode(group[gpio->group], pin[gpio->pin], GpioAf1);
            break;
        case HY_GPIO_PIN_10:
            Gpio_SetAfMode(group[gpio->group], pin[gpio->pin], GpioAf1);
            break;
        default:
            break;
    }
}

static void _init_PB_pin(HyGpio_t *gpio, en_gpio_dir_t dir, HyGpioLevel_t level)
{

}

static void _init_PC_pin(HyGpio_t *gpio, en_gpio_dir_t dir, HyGpioLevel_t level)
{

}

static void _init_PD_pin(HyGpio_t *gpio, en_gpio_dir_t dir, HyGpioLevel_t level)
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

    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);

    stc_gpio_cfg_t stcGpioCfg;
    memset(&stcGpioCfg, '\0', sizeof(stcGpioCfg));

    stcGpioCfg.enDir = dir;

    switch (gpio->pin) {
        case HY_GPIO_PIN_0:
            stcGpioCfg.enPu  = GpioPuDisable;
            stcGpioCfg.enPd  = GpioPdDisable;
            break;
        case HY_GPIO_PIN_1:
            stcGpioCfg.enPu  = GpioPuDisable;
            stcGpioCfg.enPd  = GpioPdDisable;
            break;
        default:
            break;
    }
    Gpio_Init(group[gpio->group], pin[gpio->pin], &stcGpioCfg);

    switch (gpio->pin) {
        case HY_GPIO_PIN_0:
            Gpio_SetAfMode(group[gpio->group], pin[gpio->pin], GpioAf3);
            break;
        case HY_GPIO_PIN_1:
            Gpio_SetAfMode(group[gpio->group], pin[gpio->pin], GpioAf3);
            break;
        default:
            break;
    }
}

void HyGpioSetOutput(HyGpio_t *gpio, HyGpioLevel_t level)
{
    switch (gpio->group) {
        case HY_GPIO_GROUP_PA:
            _init_PA_pin(gpio, GpioDirOut, level);
            break;
        case HY_GPIO_GROUP_PB:
            _init_PB_pin(gpio, GpioDirOut, level);
            break;
        case HY_GPIO_GROUP_PC:
            _init_PC_pin(gpio, GpioDirOut, level);
            break;
        case HY_GPIO_GROUP_PD:
            _init_PD_pin(gpio, GpioDirOut, level);
            break;
        default:
            break;
    }
}

void HyGpioSetInput(HyGpio_t *gpio)
{
    switch (gpio->group) {
        case HY_GPIO_GROUP_PA:
            _init_PA_pin(gpio, GpioDirIn, 0);
            break;
        case HY_GPIO_GROUP_PB:
            _init_PB_pin(gpio, GpioDirIn, 0);
            break;
        case HY_GPIO_GROUP_PC:
            _init_PC_pin(gpio, GpioDirIn, 0);
            break;
        case HY_GPIO_GROUP_PD:
            _init_PD_pin(gpio, GpioDirIn, 0);
            break;
        default:
            break;
    }
}

HyGpioLevel_t HyGpioGetLevel(HyGpio_t *gpio)
{
    return HY_GPIO_LEVEL_LOW;
}

void HyGpioSetLevel(HyGpio_t *gpio, HyGpioLevel_t level)
{
    en_gpio_port_t group[HY_GPIO_GROUP_MAX] = {
        GpioPortA, GpioPortB, GpioPortC, GpioPortD
    };

    en_gpio_pin_t pin[HY_GPIO_PIN_MAX] = {
        GpioPin0, GpioPin1, GpioPin2, GpioPin3,
        GpioPin4, GpioPin5, GpioPin6, GpioPin7,
        GpioPin8, GpioPin9, GpioPin10, GpioPin11,
        GpioPin12, GpioPin13, GpioPin14, GpioPin15,
    };

    if (level == HY_GPIO_LEVEL_HIGH) {
        Gpio_SetIO(group[gpio->group], pin[gpio->pin]);
    } else {
        Gpio_ClrIO(group[gpio->group], pin[gpio->pin]);
    }
}

