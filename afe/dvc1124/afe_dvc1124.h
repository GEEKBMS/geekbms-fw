/**
 * @file afe_dvc1124.h
 * @brief DVC1124 concrete device + helpers (stub for W1).
 */
#ifndef GEEKBMS_AFE_DVC1124_H
#define GEEKBMS_AFE_DVC1124_H

#include "afe_driver.h"
#include "dvc1124_regs.h"

#ifdef __cplusplus
extern "C" {
#endif

struct afe_device {
    afe_config_t cfg;
    bool         inited;
    uint32_t     balance_mask; /* software shadow until regs known */
    bool         fet_chg;
    bool         fet_dsg;
};

/** Size for static allocation in apps. */
typedef struct afe_device afe_dvc1124_dev_t;

/**
 * CRC8 per DS (poly x^8+x^2+x+1, init 0).
 * TODO(W2): verify against on-wire frames with logic analyzer.
 */
uint8_t dvc1124_crc8(const uint8_t *data, size_t len);

#ifdef __cplusplus
}
#endif

#endif /* GEEKBMS_AFE_DVC1124_H */
