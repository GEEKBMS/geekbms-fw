/**
 * @file hal_uart.h
 * @brief STM32 UART stub for telemetry (W1).
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef GEEKBMS_HAL_UART_H
#define GEEKBMS_HAL_UART_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    HAL_UART_OK = 0,
    HAL_UART_ERR_PARAM,
    HAL_UART_ERR_BUSY,
    HAL_UART_ERR_NOTIMPL
} hal_uart_status_t;

typedef struct {
    uint32_t baud; /**< e.g. 115200 */
} hal_uart_cfg_t;

hal_uart_status_t hal_uart_init(const hal_uart_cfg_t *cfg);
hal_uart_status_t hal_uart_write(const uint8_t *data, size_t len);
hal_uart_status_t hal_uart_write_str(const char *s);

#ifdef __cplusplus
}
#endif

#endif /* GEEKBMS_HAL_UART_H */
