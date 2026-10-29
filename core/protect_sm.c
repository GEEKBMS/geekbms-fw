/**
 * @file protect_sm.c
 * @brief Protect SM stub — logic skeleton only (W1).
 * SPDX-License-Identifier: Apache-2.0
 */
#include "protect_sm.h"

void protect_sm_init(protect_sm_t *sm, const protect_config_t *cfg)
{
    if (sm == 0) {
        return;
    }
    sm->state = PROTECT_ST_INIT;
    sm->last.flags = 0;
    sm->want_chg = false;
    sm->want_dsg = false;
    if (cfg) {
        sm->cfg = *cfg;
    } else {
        sm->cfg.cell_ov_mv = 3650; /* placeholder LFP-ish — NOT production */
        sm->cfg.cell_uv_mv = 2500;
        sm->cfg.fault_mask = AFE_PROT_COV | AFE_PROT_CUV | AFE_PROT_SCD |
                             AFE_PROT_OCD2 | AFE_PROT_OCC2;
    }
    sm->state = PROTECT_ST_IDLE;
}

void protect_sm_step(protect_sm_t *sm, const afe_protect_status_t *st)
{
    uint32_t f;
    if (sm == 0 || st == 0) {
        return;
    }
    sm->last = *st;
    f = st->flags & sm->cfg.fault_mask;
    if (f != 0) {
        sm->state = PROTECT_ST_FAULT;
        sm->want_chg = false;
        sm->want_dsg = false;
        return;
    }
    if (sm->state == PROTECT_ST_FAULT) {
        sm->state = PROTECT_ST_RECOVERY;
        /* TODO(W3): hysteresis / clear policy before re-enable */
        return;
    }
    sm->state = PROTECT_ST_IDLE;
    /* Default idle policy: allow both — product must override. */
    sm->want_chg = true;
    sm->want_dsg = true;
}

protect_state_t protect_sm_state(const protect_sm_t *sm)
{
    return sm ? sm->state : PROTECT_ST_INIT;
}
