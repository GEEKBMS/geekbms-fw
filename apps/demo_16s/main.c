/**
 * @file main.c
 * @brief demo_16s placeholder — not a runnable firmware image yet (W1).
 *
 * W3: init HAL + AFE, loop protect_sm + telemetry_format_csv.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "afe_driver.h"
#include "afe_dvc1124.h"
#include "protect_sm.h"
#include "telemetry.h"

#include <stdio.h>

int main(void)
{
    afe_dvc1124_dev_t afe;
    afe_config_t cfg = {
        .cell_count = 16,
        .i2c_addr7 = DVC1124_I2C_ADDR7_DEFAULT,
        .i2c_hz = DVC1124_I2C_HZ_MAX,
        .crc_enable = true,
    };
    protect_sm_t sm;
    char line[256];
    afe_status_t st;

    /* Host smoke: init + balance shadow get; no FET side effects. */
    st = afe_init(&afe, &cfg);
    if (st != AFE_OK) {
        return 1;
    }
    protect_sm_init(&sm, 0);
    (void)telemetry_format_csv(line, sizeof line, &sm, 0, 16, 0);
#if defined(GEEKBMS_HOST_SMOKE)
    puts(line);
    puts("demo_16s: host smoke OK (AFE paths mostly NOTIMPL until W2)");
#endif
    (void)afe;
    return 0;
}
