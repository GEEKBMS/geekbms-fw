/**
 * @file afe_driver.h
 * @brief Pluggable AFE driver API (geekbms-fw)
 *
 * RFC: docs/afe_driver_rfc.md
 * License: Apache-2.0
 *
 * Compile-time driver selection (W1): define AFE_DRIVER_DVC1124 when linking
 * afe/dvc1124. Runtime vtable deferred.
 */
#ifndef GEEKBMS_AFE_DRIVER_H
#define GEEKBMS_AFE_DRIVER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define AFE_API_VERSION_MAJOR 0
#define AFE_API_VERSION_MINOR 1

/** Hardware max for DVC1124 class monitors in this project. */
#define AFE_MAX_CELLS 24

typedef enum {
    AFE_OK = 0,
    AFE_ERR_PARAM,
    AFE_ERR_IO,
    AFE_ERR_CRC,
    AFE_ERR_TIMEOUT,
    AFE_ERR_NOTSUP,
    AFE_ERR_NOTIMPL,
    AFE_ERR_STATE
} afe_status_t;

#define AFE_PROT_COV   (1u << 0)
#define AFE_PROT_CUV   (1u << 1)
#define AFE_PROT_OCC1  (1u << 2)
#define AFE_PROT_OCD1  (1u << 3)
#define AFE_PROT_OCC2  (1u << 4)
#define AFE_PROT_OCD2  (1u << 5)
#define AFE_PROT_SCD   (1u << 6)
#define AFE_PROT_OT    (1u << 7)
#define AFE_PROT_UT    (1u << 8)
#define AFE_PROT_IWDG  (1u << 9)

typedef struct {
    uint32_t flags; /**< AFE_PROT_* */
} afe_protect_status_t;

typedef struct {
    uint8_t  cell_count; /**< 5..AFE_MAX_CELLS */
    uint8_t  i2c_addr7;  /**< DVC1124 typical 0x20 (W=0x40/R=0x41) */
    uint32_t i2c_hz;     /**< typically 100000 */
    bool     crc_enable;
} afe_config_t;

/**
 * Opaque device. Concrete layout lives in the selected driver.
 * Apps/core hold a pointer; do not depend on size across drivers.
 */
typedef struct afe_device afe_device_t;

typedef void (*afe_reg_dump_cb_t)(void *ctx, uint8_t reg_addr, uint8_t value);

afe_status_t afe_init(afe_device_t *dev, const afe_config_t *cfg);
afe_status_t afe_reset(afe_device_t *dev);

/** Cell voltages in millivolts; count must equal cfg.cell_count from init. */
afe_status_t afe_read_cells(afe_device_t *dev, int32_t *mv, size_t count);
afe_status_t afe_read_pack_mv(afe_device_t *dev, int32_t *mv);
afe_status_t afe_read_current_ma(afe_device_t *dev, int32_t *ma);
afe_status_t afe_read_temps_c(afe_device_t *dev, int16_t *celsius, size_t n);

/** Bit0 = cell 1, Bit23 = cell 24. */
afe_status_t afe_balance_set(afe_device_t *dev, uint32_t mask);
afe_status_t afe_balance_get(afe_device_t *dev, uint32_t *mask);

afe_status_t afe_protect_status(afe_device_t *dev, afe_protect_status_t *st);
afe_status_t afe_protect_clear(afe_device_t *dev, uint32_t mask);

/**
 * Request charge/discharge high-side path state.
 * DANGEROUS — call only from core policy after safety checks.
 */
afe_status_t afe_fet_set(afe_device_t *dev, bool chg_on, bool dsg_on);
afe_status_t afe_fet_get(afe_device_t *dev, bool *chg_on, bool *dsg_on);

/** Debug: dump register window (e.g. 0x00..0x8F). May return NOTIMPL. */
afe_status_t afe_dump_regs(afe_device_t *dev, afe_reg_dump_cb_t cb, void *ctx);

#ifdef __cplusplus
}
#endif

#endif /* GEEKBMS_AFE_DRIVER_H */
