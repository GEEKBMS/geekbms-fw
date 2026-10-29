/**
 * @file afe_dvc1124.c
 * @brief DVC1124 AFE driver stub — compiles conceptually; I2C path W2.
 *
 * Copyright 2026 GEEKBMS contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#include "afe_dvc1124.h"

#include <string.h>

/* HAL hooks — provided by hal/stm32 when linked; weak stubs for host builds. */
#if defined(GEEKBMS_HAS_HAL_I2C)
#include "hal_i2c.h"
#endif

uint8_t dvc1124_crc8(const uint8_t *data, size_t len)
{
    uint8_t crc = DVC1124_CRC8_INIT;
    size_t i, b;
    if (data == NULL && len > 0) {
        return 0;
    }
    for (i = 0; i < len; i++) {
        crc ^= data[i];
        for (b = 0; b < 8u; b++) {
            if (crc & 0x80u) {
                crc = (uint8_t)((crc << 1) ^ DVC1124_CRC8_POLY);
            } else {
                crc <<= 1;
            }
        }
    }
    return crc;
}

afe_status_t afe_init(afe_device_t *dev, const afe_config_t *cfg)
{
    if (dev == NULL || cfg == NULL) {
        return AFE_ERR_PARAM;
    }
    if (cfg->cell_count < DVC1124_CELLS_MIN ||
        cfg->cell_count > DVC1124_CELLS_MAX) {
        return AFE_ERR_PARAM;
    }
    memset(dev, 0, sizeof(*dev));
    dev->cfg = *cfg;
    if (dev->cfg.i2c_addr7 == 0) {
        dev->cfg.i2c_addr7 = DVC1124_I2C_ADDR7_DEFAULT;
    }
    if (dev->cfg.i2c_hz == 0) {
        dev->cfg.i2c_hz = DVC1124_I2C_HZ_MAX;
    }
    /* TODO(W2): I2C probe + soft config from DS once reg map filled. */
    dev->inited = true;
    return AFE_OK;
}

afe_status_t afe_reset(afe_device_t *dev)
{
    if (dev == NULL || !dev->inited) {
        return AFE_ERR_PARAM;
    }
    /* TODO(W2): DS shutdown/sleep/wake commands — offsets TBD. */
    (void)dev;
    return AFE_ERR_NOTIMPL;
}

afe_status_t afe_read_cells(afe_device_t *dev, int32_t *mv, size_t count)
{
    size_t i;
    if (dev == NULL || !dev->inited || mv == NULL) {
        return AFE_ERR_PARAM;
    }
    if (count != (size_t)dev->cfg.cell_count) {
        return AFE_ERR_PARAM;
    }
    /* TODO(W2): burst-read cell voltage regs (addresses TBD). */
    for (i = 0; i < count; i++) {
        mv[i] = 0;
    }
    return AFE_ERR_NOTIMPL;
}

afe_status_t afe_read_pack_mv(afe_device_t *dev, int32_t *mv)
{
    if (dev == NULL || !dev->inited || mv == NULL) {
        return AFE_ERR_PARAM;
    }
    *mv = 0;
    /* TODO(W2): C24-VSS or sum — reg TBD. */
    return AFE_ERR_NOTIMPL;
}

afe_status_t afe_read_current_ma(afe_device_t *dev, int32_t *ma)
{
    if (dev == NULL || !dev->inited || ma == NULL) {
        return AFE_ERR_PARAM;
    }
    *ma = 0;
    /* Needs Rsense config struct (RFC). */
    return AFE_ERR_NOTIMPL;
}

afe_status_t afe_read_temps_c(afe_device_t *dev, int16_t *celsius, size_t n)
{
    size_t i;
    if (dev == NULL || !dev->inited || (celsius == NULL && n > 0)) {
        return AFE_ERR_PARAM;
    }
    for (i = 0; i < n; i++) {
        celsius[i] = 0;
    }
    return AFE_ERR_NOTIMPL;
}

afe_status_t afe_balance_set(afe_device_t *dev, uint32_t mask)
{
    if (dev == NULL || !dev->inited) {
        return AFE_ERR_PARAM;
    }
    /* Shadow only — must not claim hardware balance until regs known. */
    dev->balance_mask = mask & ((1u << dev->cfg.cell_count) - 1u);
    /* TODO(W2): write balance control bits; enforce odd/even policy. */
    return AFE_ERR_NOTIMPL;
}

afe_status_t afe_balance_get(afe_device_t *dev, uint32_t *mask)
{
    if (dev == NULL || !dev->inited || mask == NULL) {
        return AFE_ERR_PARAM;
    }
    *mask = dev->balance_mask;
    return AFE_OK;
}

afe_status_t afe_protect_status(afe_device_t *dev, afe_protect_status_t *st)
{
    if (dev == NULL || !dev->inited || st == NULL) {
        return AFE_ERR_PARAM;
    }
    st->flags = 0;
    /* TODO(W2): map COV/CUV/OCx/SCD flags from DS. */
    return AFE_ERR_NOTIMPL;
}

afe_status_t afe_protect_clear(afe_device_t *dev, uint32_t mask)
{
    if (dev == NULL || !dev->inited) {
        return AFE_ERR_PARAM;
    }
    (void)mask;
    return AFE_ERR_NOTIMPL;
}

afe_status_t afe_fet_set(afe_device_t *dev, bool chg_on, bool dsg_on)
{
    if (dev == NULL || !dev->inited) {
        return AFE_ERR_PARAM;
    }
    /* Refuse silent hardware side effects in stub. */
    dev->fet_chg = chg_on;
    dev->fet_dsg = dsg_on;
    /* TODO(W2): charge pump + CHG/DSG — NEVER enable by default on init. */
    return AFE_ERR_NOTIMPL;
}

afe_status_t afe_fet_get(afe_device_t *dev, bool *chg_on, bool *dsg_on)
{
    if (dev == NULL || !dev->inited || chg_on == NULL || dsg_on == NULL) {
        return AFE_ERR_PARAM;
    }
    *chg_on = dev->fet_chg;
    *dsg_on = dev->fet_dsg;
    return AFE_OK;
}

afe_status_t afe_dump_regs(afe_device_t *dev, afe_reg_dump_cb_t cb, void *ctx)
{
    if (dev == NULL || !dev->inited || cb == NULL) {
        return AFE_ERR_PARAM;
    }
    (void)ctx;
    /* TODO(W2): sequential read 0x00..0x8F with CRC frames. */
    return AFE_ERR_NOTIMPL;
}
