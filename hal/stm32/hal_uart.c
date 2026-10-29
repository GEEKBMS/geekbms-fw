/**
 * @file hal_uart.c
 * @brief STM32 UART stub (W1).
 * SPDX-License-Identifier: Apache-2.0
 */
#include "hal_uart.h"

#include <string.h>

hal_uart_status_t hal_uart_init(const hal_uart_cfg_t *cfg)
{
    (void)cfg;
    /* TODO(W2): USART init for demo board. */
    return HAL_UART_ERR_NOTIMPL;
}

hal_uart_status_t hal_uart_write(const uint8_t *data, size_t len)
{
    (void)data;
    (void)len;
    return HAL_UART_ERR_NOTIMPL;
}

hal_uart_status_t hal_uart_write_str(const char *s)
{
    if (s == 0) {
        return HAL_UART_ERR_PARAM;
    }
    return hal_uart_write((const uint8_t *)s, strlen(s));
}
