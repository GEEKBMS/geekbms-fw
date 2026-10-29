/**
 * @file protect_sm.h
 * @brief Minimal battery protect state machine (W1 stub).
 *
 * Apps call protect_sm_step() after afe_protect_status / afe_read_*.
 * FET requests go only through this module (see afe_driver_rfc.md).
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef GEEKBMS_PROTECT_SM_H
#define GEEKBMS_PROTECT_SM_H

#include <stdbool.h>
#include <stdint.h>

#include "afe_driver.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    PROTECT_ST_INIT = 0,
    PROTECT_ST_IDLE,       /* monitoring, FETs policy-dependent */
    PROTECT_ST_FAULT,      /* latched fault — FETs requested off */
    PROTECT_ST_RECOVERY    /* waiting clear conditions */
} protect_state_t;

typedef struct {
    int32_t cell_ov_mv;
    int32_t cell_uv_mv;
    uint32_t fault_mask; /* which AFE_PROT_* force FAULT */
} protect_config_t;

typedef struct {
    protect_state_t state;
    protect_config_t cfg;
    afe_protect_status_t last;
    bool want_chg;
    bool want_dsg;
} protect_sm_t;

void protect_sm_init(protect_sm_t *sm, const protect_config_t *cfg);

/**
 * @brief One step: update state from AFE flags; set want_chg/want_dsg.
 * Does not call afe_fet_set — caller applies after review (W3 wires this).
 */
void protect_sm_step(protect_sm_t *sm, const afe_protect_status_t *st);

protect_state_t protect_sm_state(const protect_sm_t *sm);

#ifdef __cplusplus
}
#endif

#endif /* GEEKBMS_PROTECT_SM_H */
