/**
 * @file hal_i2c.c
 * @brief STM32 I2C stub — returns NOTIMPL until board bring-up (W2).
 * SPDX-License-Identifier: Apache-2.0
 */
#include "hal_i2c.h"

hal_i2c_status_t hal_i2c_init(const hal_i2c_cfg_t *cfg)
{
    (void)cfg;
    /* TODO(W2): MX_I2Cx_Init, timing for 100 kHz, enable. */
    return HAL_I2C_ERR_NOTIMPL;
}

hal_i2c_status_t hal_i2c_probe(uint8_t addr7)
{
    (void)addr7;
    return HAL_I2C_ERR_NOTIMPL;
}

hal_i2c_status_t hal_i2c_write(uint8_t addr7, const uint8_t *data, size_t len)
{
    (void)addr7;
    (void)data;
    (void)len;
    return HAL_I2C_ERR_NOTIMPL;
}

hal_i2c_status_t hal_i2c_read(uint8_t addr7, uint8_t *data, size_t len)
{
    (void)addr7;
    (void)data;
    (void)len;
    return HAL_I2C_ERR_NOTIMPL;
}

hal_i2c_status_t hal_i2c_write_read(uint8_t addr7,
                                    const uint8_t *wdata, size_t wlen,
                                    uint8_t *rdata, size_t rlen)
{
    (void)addr7;
    (void)wdata;
    (void)wlen;
    (void)rdata;
    (void)rlen;
    return HAL_I2C_ERR_NOTIMPL;
}
