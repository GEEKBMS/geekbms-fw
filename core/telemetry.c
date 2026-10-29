/**
 * @file telemetry.c
 * SPDX-License-Identifier: Apache-2.0
 */
#include "telemetry.h"

#include <stdio.h>

size_t telemetry_format_csv(char *buf, size_t buflen,
                            const protect_sm_t *sm,
                            const int32_t *cell_mv, size_t ncells,
                            uint32_t balance_mask)
{
    size_t off = 0;
    int n;
    size_t i;
    if (buf == 0 || buflen < 8 || sm == 0) {
        return 0;
    }
    n = snprintf(buf + off, buflen - off, "%d,0x%lx",
                 (int)sm->state, (unsigned long)sm->last.flags);
    if (n < 0 || (size_t)n >= buflen - off) {
        return 0;
    }
    off += (size_t)n;
    for (i = 0; i < ncells; i++) {
        int32_t v = cell_mv ? cell_mv[i] : 0;
        n = snprintf(buf + off, buflen - off, ",%ld", (long)v);
        if (n < 0 || (size_t)n >= buflen - off) {
            return 0;
        }
        off += (size_t)n;
    }
    n = snprintf(buf + off, buflen - off, ",0x%lx\n",
                 (unsigned long)balance_mask);
    if (n < 0 || (size_t)n >= buflen - off) {
        return 0;
    }
    off += (size_t)n;
    return off;
}
