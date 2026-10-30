# RFC: `afe_driver.h` — 可插拔 AFE 驱动接口（冻结提案）

**状态：** W1 提案 · 拟在 W2 合入前冻结 v0  
**日期：** 2026-10-29（Asia/Shanghai）  
**范围：** C99；无动态分配；嵌入式友好

## 目标

让 `core` 与 `apps` 在更换 AFE（DVC1124 → 其他）时只需链接不同实现，不改保护状态机签名。

## 非目标

- 不规定 RTOS  
- 不规定具体寄存器地址  
- 不在接口层暴露 I²C CRC 细节（留在芯片驱动内）

## 错误码

```c
typedef enum {
    AFE_OK = 0,
    AFE_ERR_PARAM,
    AFE_ERR_IO,
    AFE_ERR_CRC,
    AFE_ERR_TIMEOUT,
    AFE_ERR_NOTSUP,   /* 该 AFE 无此能力 */
    AFE_ERR_NOTIMPL,  /* 已知需求但尚未实现 / 寄存器 TBD */
    AFE_ERR_STATE
} afe_status_t;
```

## 能力与配置

```c
#define AFE_MAX_CELLS 24

typedef struct {
    uint8_t  cell_count;     /* 5..24 for DVC1124 */
    uint8_t  i2c_addr7;      /* DVC1124 typical 0x20 */
    uint32_t i2c_hz;         /* typically 100000 */
    bool     crc_enable;     /* DS: CRC8 optional path */
} afe_config_t;

typedef struct afe_device afe_device_t; /* opaque or vtable holder */
```

## 核心 API（提案）

| 函数 | 语义 |
|------|------|
| `afe_init(dev, cfg)` | 探测/软复位策略由驱动定义；失败不默认开 FET |
| `afe_reset(dev)` | 软复位或重新加载默认；**TBD** 若 DS 无公开命令则 `NOTIMPL` |
| `afe_read_cells(dev, mv[], count)` | 电芯电压 mV；`count == cfg.cell_count` |
| `afe_read_pack_mv(dev, *mv)` | 总压或等效（C24–VSS 等）；能力不足则 `NOTSUP` |
| `afe_read_current_ma(dev, *ma)` | 分流换算后的电流；需外部 Rsense 配置（后续扩展） |
| `afe_read_temps_c(dev, c[], n)` | 内核 + 外部 NTC；通道映射驱动私有 |
| `afe_balance_set(dev, mask)` | bit0 = cell1…；奇偶交替策略可在驱动或 core |
| `afe_balance_get(dev, *mask)` | 读回 |
| `afe_protect_status(dev, *st)` | OV/UV/OCx/SCD 等标准化位 |
| `afe_protect_clear(dev, mask)` | 清除锁存（若硬件允许） |
| `afe_fet_set(dev, chg, dsg)` | 请求高边充/放电路径；**危险**，须经 core 门控 |
| `afe_fet_get(dev, *chg, *dsg)` | 读回请求/状态 |
| `afe_dump_regs(dev, cb, ctx)` | 调试：按字节回调 0x00..0x8F 窗口（长度芯片相关） |

### 保护状态位（标准化）

```c
typedef struct {
    uint32_t flags; /* AFE_PROT_* */
} afe_protect_status_t;

#define AFE_PROT_COV   (1u << 0)
#define AFE_PROT_CUV   (1u << 1)
#define AFE_PROT_OCC1  (1u << 2)
#define AFE_PROT_OCD1  (1u << 3)
#define AFE_PROT_OCC2  (1u << 4)
#define AFE_PROT_OCD2  (1u << 5)
#define AFE_PROT_SCD   (1u << 6)
#define AFE_PROT_OT    (1u << 7)  /* die or NTC, mapped by driver */
#define AFE_PROT_UT    (1u << 8)
#define AFE_PROT_IWDG  (1u << 9)  /* I2C watchdog if present */
```

## Vtable 可选形态

W1 头文件采用**直接 C 函数 + 单编译期驱动**（`#define AFE_DRIVER_DVC1124`）。若 W3 需要运行时切换仿真器，再引入：

```c
typedef struct {
    afe_status_t (*init)(afe_device_t *, const afe_config_t *);
    /* ... */
} afe_driver_ops_t;
```

## 冻结规则

1. 删减 API 须发新 RFC；新增可加在文件末尾并 bump `AFE_API_VERSION`。  
2. 标准化标志位只增不改语义。  
3. 芯片私有寄存器名不得泄漏到 `core/`。

## 评审清单（W1→W2）

- [ ] `cell_count` 与屏蔽未用通道的责任在 core 还是 driver？**提案：driver 负责硬件屏蔽，core 给逻辑串数。**  
- [ ] `afe_fet_set` 是否允许 app 直调？**提案：仅 core；app 调 core 策略。**  
- [ ] 电流 API 是否推迟到 W3？**提案：头文件保留，DVC1124 stub 返回 `NOTIMPL` 直至 Rsense 配置结构合并。**

头文件实现见 [`../afe/include/afe_driver.h`](../afe/include/afe_driver.h)。
