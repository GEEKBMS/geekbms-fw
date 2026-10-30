/**
 * @file hal_i2c.h
 * @brief STM32 I2C host stub for geekbms-fw (W1).
 *
 * First MCU port: STM32. Concrete Cube/HAL init is board-specific (W2).
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef GEEKBMS_HAL_I2C_H
#define GEEKBMS_HAL_I2C_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    HAL_I2C_OK = 0,
    HAL_I2C_ERR_PARAM,
    HAL_I2C_ERR_NACK,
    HAL_I2C_ERR_BUS,
    HAL_I2C_ERR_NOTIMPL
} hal_i2c_status_t;

typedef struct {
    uint32_t clk_hz; /**< DVC1124: 100 kHz */
} hal_i2c_cfg_t;

hal_i2c_status_t hal_i2c_init(const hal_i2c_cfg_t *cfg);
hal_i2c_status_t hal_i2c_probe(uint8_t addr7);
hal_i2c_status_t hal_i2c_write(uint8_t addr7, const uint8_t *data, size_t len);
hal_i2c_status_t hal_i2c_read(uint8_t addr7, uint8_t *data, size_t len);

/**
 * Combined write-then-read (repeated start) for register access.
 * TODO(W2): map to HAL_I2C_Mem_Read / LL.
 */
hal_i2c_status_t hal_i2c_write_read(uint8_t addr7,
                                    const uint8_t *wdata, size_t wlen,
                                    uint8_t *rdata, size_t rlen);

#ifdef __cplusplus
}
#endif

#endif /* GEEKBMS_HAL_I2C_H */
