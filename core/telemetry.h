/**
 * @file telemetry.h
 * @brief UART text telemetry helpers (W1 header; format frozen in W3).
 */
#ifndef GEEKBMS_TELEMETRY_H
#define GEEKBMS_TELEMETRY_H

#include <stddef.h>
#include <stdint.h>

#include "afe_driver.h"
#include "protect_sm.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Format one CSV line: state,flags,cell0_mv,... 
 * Returns bytes written (excluding NUL) or 0 on error.
 * TODO(W3): JSON option; document exact column order in docs/.
 */
size_t telemetry_format_csv(char *buf, size_t buflen,
                            const protect_sm_t *sm,
                            const int32_t *cell_mv, size_t ncells,
                            uint32_t balance_mask);

#ifdef __cplusplus
}
#endif

#endif /* GEEKBMS_TELEMETRY_H */
