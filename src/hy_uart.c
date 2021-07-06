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

#include "at32f4xx_gpio.h"

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

        GPIO_InitType GPIO_InitStructure;

        GPIO_StructInit(&GPIO_InitStructure);
        GPIO_InitStructure.GPIO_Pins = uart_pin[i].tx_pin; 
        GPIO_InitStructure.GPIO_MaxSpeed = GPIO_MaxSpeed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;

        GPIO_Init(uart_pin[i].gpiox, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Pins = uart_pin[i].rx_pin;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_PD;

        GPIO_Init(uart_pin[i].gpiox, &GPIO_InitStructure);

        break;
    }
}

static void _init_uart_func(HyUartNum_t num, uint32_t rate)
{
    USART_InitType USART_InitStructure;
    USART_Type* uart[HY_UART_MAX] = {NULL, USART1, USART2, USART3, UART4, UART5};

    USART_StructInit(&USART_InitStructure);
    USART_InitStructure.USART_BaudRate              = rate;
    USART_InitStructure.USART_WordLength            = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits              = USART_StopBits_1;
    USART_InitStructure.USART_Parity                = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl   = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode                  = USART_Mode_Rx | USART_Mode_Tx;	

    USART_Init(uart[num], &USART_InitStructure); 
}

typedef struct {
    USART_Type  *uart;
    uint8_t     NVIC_IRQChannel;
    uint8_t     NVIC_IRQChannelSubPriority;
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

    NVIC_InitType NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel                      = uart_interrupt[num].NVIC_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority    = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority           = uart_interrupt[num].NVIC_IRQChannelSubPriority;
    NVIC_InitStructure.NVIC_IRQChannelCmd                   = ENABLE;

    NVIC_Init(&NVIC_InitStructure);

    USART_INTConfig(uart_interrupt[num].uart, USART_INT_RDNE, ENABLE);
    USART_Cmd(uart_interrupt[num].uart, ENABLE);
}

void *HyUartCreate(HyUartConfig_t *uart_config)
{
    _uart_context_t *context = NULL;

    do {
        context = malloc(sizeof(*context));
        if (!context) {
            break;
        }
        memset(context, '\0', sizeof(*context));

        context->num = uart_config->num;
        memcpy(&context->config_save, &uart_config->config_save,
                sizeof(context->config_save));

        _init_uart_gpio(uart_config->num);
        _init_uart_func(uart_config->num, uart_config->rate);
        _init_uart_interrupt(uart_config->num);

        context_array[uart_config->num] = context;

        return context;
    } while (0);

    return NULL;
}

void HyUartDestroy(void *handle)
{
    if (handle) {
        _uart_context_t *context = handle;

        context_array[context->num] = NULL;

        free(context);
    }
}

static void _uart_irq_handler(HyUartNum_t num)
{
    if (context_array[num]) {
        HyUartConfigSave_t *config_save = &context_array[num]->config_save;
        USART_Type *uart[HY_UART_MAX] = {NULL, USART1, USART2, USART3, UART4, UART5};

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
    if (!handle) {
        return -1;
    }

    _uart_context_t *context = handle;
    USART_Type* uart[HY_UART_MAX] = {NULL, USART1, USART2, USART3, UART4, UART5};
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
    if (!handle) {
        return -1;
    }

    _uart_context_t *context = handle;
    USART_Type* uart[HY_UART_MAX] = {NULL, USART1, USART2, USART3, UART4, UART5};
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

