/**
 * @file dvc1124_regs.h
 * @brief DVC1124 constants from public DS V0.6 — NO invented offsets.
 *
 * Datasheet:
 * https://bms.pub/uploads/soft/Datasheet/DVC1124%E6%95%B0%E6%8D%AE%E6%89%8B%E5%86%8C_V0.6.pdf
 *
 * Register byte addresses are TBD until filled from a complete map.
 */
#ifndef GEEKBMS_DVC1124_REGS_H
#define GEEKBMS_DVC1124_REGS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** 7-bit address corresponding to write 0x40 / read 0x41 (DS). */
#define DVC1124_I2C_ADDR7_DEFAULT 0x20u

#define DVC1124_I2C_HZ_MAX 100000u

/** Register address window (DS): 0x00 .. 0x8F inclusive. */
#define DVC1124_REG_ADDR_MIN 0x00u
#define DVC1124_REG_ADDR_MAX 0x8Fu
#define DVC1124_REG_COUNT    0x90u /* 144 */

#define DVC1124_CELLS_MIN 5u
#define DVC1124_CELLS_MAX 24u

/** Passive balance drive current upper bound (recommended, DS). */
#define DVC1124_BALANCE_MA_MAX 25u

/** CRC8 polynomial x^8+x^2+x+1, init 0x00 (DS). */
#define DVC1124_CRC8_POLY 0x07u
#define DVC1124_CRC8_INIT 0x00u

/*
 * Logical names appear in DS prose; offsets intentionally absent.
 * Example placeholders for future fill-in:
 *
 * #define DVC1124_REG_COV_FLAG  0x??  // TBD
 * #define DVC1124_REG_CUV_FLAG  0x??  // TBD
 */

#ifdef __cplusplus
}
#endif

#endif /* GEEKBMS_DVC1124_REGS_H */
