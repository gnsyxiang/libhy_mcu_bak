/**
 * 
 * Release under GPLv-3.0.
 * 
 * @file    hy_uart.c
 * @brief   
 * @author  gnsyxiang <gnsyxiang@163.com>
 * @date    06/07 2021 16:08
 * @version v0.0.1
 * 
 * @since    note
 * @note     note
 * 
 *     change log:
 *     NO.     Author              Date            Modified
 *     00      zhenquan.qiu        06/07 2021      create the file
 * 
 *     last modified: 06/07 2021 16:08
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hy_uart.h"

#include "hy_utils/hy_log.h"
#include "hy_utils/hy_mem.h"
#include "hy_utils/hy_string.h"
#include "hy_utils/hy_assert.h"

#include "at32f4xx_gpio.h"

#define ALONE_DEBUG 1

typedef struct {
    HyUartNum_t num;

    HyUartConfigSave_t config_save;
} _uart_context_t;

static _uart_context_t *context_array[HY_UART_MAX] = {NULL};

typedef struct {
    HyUartNum_t     uart;
    GPIO_Type*      gpiox;
    uint16_t        tx_pin;
    uint16_t        rx_pin;
} _uart_pin_t;

typedef struct {
    uint32_t        uart_rcc;
    uint32_t        gpio_rcc;
    uint32_t        gpio_remap;
    FunctionalState new_state;
} _uart_rcc_t;

static void _init_uart_gpio(HyUartNum_t num)
{
    _uart_pin_t uart_pin[] = {
        {HY_UART_1, GPIOA, GPIO_Pins_9,  GPIO_Pins_10},
        {HY_UART_4, GPIOC, GPIO_Pins_10, GPIO_Pins_11},
        {HY_UART_5, GPIOB, GPIO_Pins_9,  GPIO_Pins_8},
    };
    _uart_rcc_t uart_rcc[] = {
        {RCC_APB2PERIPH_USART1, RCC_APB2PERIPH_GPIOA,                        0, ENABLE},
        {RCC_APB1PERIPH_UART4,  RCC_APB2PERIPH_GPIOC,                        0, ENABLE},
        {RCC_APB1PERIPH_UART5,  RCC_APB2PERIPH_GPIOB | RCC_APB2PERIPH_AFIO,  AFIO_MAP5_USART5_0001, ENABLE},
    };

    for (int i = 0; i < HY_UART_MAX; i++) {
        if (num != uart_pin[i].uart) {
            continue;
        }

        RCC_APB2PeriphClockCmd(uart_rcc[i].gpio_rcc, ENABLE);
        if (HY_UART_1 == num) {
            RCC_APB2PeriphClockCmd(uart_rcc[i].uart_rcc, ENABLE);
        } else {
            RCC_APB1PeriphClockCmd(uart_rcc[i].uart_rcc, ENABLE);
        }
        if (uart_rcc[i].gpio_remap) {
            GPIO_PinsRemapConfig(uart_rcc[i].gpio_remap, uart_rcc[i].new_state);
        }

        GPIO_InitType gpio;

        GPIO_StructInit(&gpio);
        gpio.GPIO_Pins      = uart_pin[i].tx_pin; 
        gpio.GPIO_MaxSpeed  = GPIO_MaxSpeed_50MHz;
        gpio.GPIO_Mode      = GPIO_Mode_AF_PP;

        GPIO_Init(uart_pin[i].gpiox, &gpio);

        gpio.GPIO_Pins      = uart_pin[i].rx_pin;
        gpio.GPIO_Mode      = GPIO_Mode_IN_PD;

        GPIO_Init(uart_pin[i].gpiox, &gpio);

        break;
    }
}

static void _init_uart_func(HyUartNum_t num, uint32_t rate)
{
    USART_InitType uart;
    USART_Type* uart_num[HY_UART_MAX] = {
        NULL, USART1, USART2, USART3, UART4, UART5
    };

    USART_StructInit(&uart);
    uart.USART_BaudRate              = rate;
    uart.USART_WordLength            = USART_WordLength_8b;
    uart.USART_StopBits              = USART_StopBits_1;
    uart.USART_Parity                = USART_Parity_No;
    uart.USART_HardwareFlowControl   = USART_HardwareFlowControl_None;
    uart.USART_Mode                  = USART_Mode_Rx | USART_Mode_Tx;	

    USART_Init(uart_num[num], &uart); 
}

typedef struct {
    USART_Type  *uart;
    uint8_t     ch;
    uint8_t     sub_priority;
} _uart_interrupt_t;

static void _init_uart_interrupt(HyUartNum_t num)
{
    _uart_interrupt_t uart_interrupt[] = {
        {NULL,      0,              0},
        {USART1,    USART1_IRQn,    1},
        {USART2,    USART1_IRQn,    2},
        {USART3,    USART1_IRQn,    3},
        {UART4,     UART4_IRQn,     4},
        {UART5,     UART5_IRQn,     5},
    };

    NVIC_InitType nvic;
    nvic.NVIC_IRQChannel                      = uart_interrupt[num].ch;
    nvic.NVIC_IRQChannelPreemptionPriority    = 0;
    nvic.NVIC_IRQChannelSubPriority           = uart_interrupt[num].sub_priority;
    nvic.NVIC_IRQChannelCmd                   = ENABLE;

    NVIC_Init(&nvic);

    USART_INTConfig(uart_interrupt[num].uart, USART_INT_RDNE, ENABLE);
    USART_Cmd(uart_interrupt[num].uart, ENABLE);
}

static void _uart_irq_handler(HyUartNum_t num)
{
    if (context_array[num]) {
        HyUartConfigSave_t *config_save = &context_array[num]->config_save;
        USART_Type *uart[HY_UART_MAX] = {
            NULL, USART1, USART2, USART3, UART4, UART5
        };

        if(USART_GetITStatus(uart[num], USART_INT_RDNE) != RESET) {
            if (config_save->read_cb) {
                config_save->read_cb(USART_ReceiveData(uart[num]), config_save->args);
            }
        }
    }
}

void USART1_IRQHandler(void)
{
    _uart_irq_handler(HY_UART_1);
}

void UART4_IRQHandler(void)
{
    _uart_irq_handler(HY_UART_4);
}

void UART5_IRQHandler(void)
{
    _uart_irq_handler(HY_UART_5);
}

int HyUartSendByte(void *handle, char byte)
{
    HY_ASSERT_NULL_RET_VAL(!handle, -1);

    _uart_context_t *context = handle;
    USART_Type* uart[HY_UART_MAX] = {
        NULL, USART1, USART2, USART3, UART4, UART5
    };
    FlagStatus Status = RESET;
    uint32_t Count=0;

    USART_SendData(uart[context->num], byte);
    do {
        Status = USART_GetFlagStatus(uart[context->num], USART_FLAG_TRAC);
        Count++;
    } while((Status == RESET) && (Count != 0x1CE2));

    if(Count == 0x1CE2)
        return (EOF);

    return (byte);
}

int HyUartSendBuf(void *handle, void *buf, size_t len)
{
    HY_ASSERT_NULL_RET_VAL(!handle, -1);

    _uart_context_t *context = handle;
    USART_Type* uart[HY_UART_MAX] = {
        NULL, USART1, USART2, USART3, UART4, UART5
    };
    FlagStatus Status = RESET;
    uint32_t Count=0;
    uint16_t i = 0;
    char *str = buf;

    do {
        Count = 0;
        USART_SendData(uart[context->num], str[i]);
        do {
            Status = USART_GetFlagStatus(uart[context->num], USART_FLAG_TRAC);
            Count++;
        } while((Status == RESET) && (Count != 0x1CE2));

        if(Count == 0x1CE2) {
            break;
        }
        i++;
    } while (i < len);

    return (i);
}

void HyUartDestroy(void **handle)
{
    LOGT("%s:%d \n", __func__, __LINE__);

    if (handle && *handle) {
        _uart_context_t *context = *handle;

        context_array[context->num] = NULL;

        HY_FREE(handle);
    }
}

void *HyUartCreate(HyUartConfig_t *uart_config)
{
    LOGT("%s:%d \n", __func__, __LINE__);

    HY_ASSERT_NULL_RET_VAL(!uart_config, NULL);

    _uart_context_t *context = NULL;

    do {
        context = HY_MALLOC_BREAK(sizeof(*context));

        context_array[uart_config->num] = context;
        context->num                    = uart_config->num;

        HY_MEMCPY(&context->config_save, &uart_config->config_save);

        _init_uart_gpio(uart_config->num);
        _init_uart_func(uart_config->num, uart_config->rate);
        _init_uart_interrupt(uart_config->num);

        return context;
    } while (0);

    HyUartDestroy((void **)&context);

    return NULL;
}

#ifdef DEBUG_UART

int _write(int fd, char *ptr, int len)
{
    /*
     * write "len" of char from "ptr" to file id "fd"
     * Return number of char written.
     *
     * Only work for STDOUT, STDIN, and STDERR
     */
    if (fd > 2) {
        return -1;
    }

    int i = 0;
    while (*ptr && (i < len)) {
        HyUartSendByte(context_array[DEBUG_UART_NUM], *ptr);
        if (*ptr == '\n') {
            HyUartSendByte(context_array[DEBUG_UART_NUM], '\r');
        }
        i++;
        ptr++;
    }
    return i;
}

void HyUartDebugDestroy(void **handle)
{
    LOGT("%s:%d \n", __func__, __LINE__);

    if (handle && *handle) {
        HyUartDestroy(handle);
    }
}

void *HyUartDebugCreate(HyUartConfig_t *uart_config)
{
    LOGT("%s:%d \n", __func__, __LINE__);

    return HyUartCreate(uart_config);
}

#endif

