# geekbms-fw

> **安全免责（请先读）**  
> 锂电池组与高压母线（常见 48–100 V）有起火、电击与人身伤害风险。本仓库仅为**研究与教育用途**的开源固件框架，**不是**功能安全认证产品，**不得**直接装车或当作量产 BMS。错误接线、错误阈值或错误 FET 控制可能导致严重后果。贡献者与 GEEKBMS **不承担**因使用、修改或集成本软件导致的任何损失。完整声明见 [`SECURITY.md`](SECURITY.md) 与 [`docs/safety.md`](docs/safety.md)。

两轮车领域可插拔 AFE 的 **BMS 开源固件框架**。首发驱动南京集澈 / 宜矽源 **DVC1124**（5–24S、高边 NFET、被动均衡），首发 MCU：**STM32**。许可：**Apache-2.0**。

English blurb: Pluggable AFE firmware framework for light EV (e-bike / e-scooter / light motorcycle) BMS. First driver: DVC1124; first MCU port: STM32. Research / education only — not a certified product.

## 定位

- **做：** 可审计的 `afe_driver` 接口 + DVC1124 实现骨架 + 最小保护状态机 + UART 遥测 + 主机 dump/参数工具入口。
- **不做（v0.1）：** 量产 BOM / 完整 PCB、CAN/BLE/OTA、主动均衡、精确 SOC/SOH、竞品协议兼容、任何「已上车 / 替代大厂」声称。

相对 [LibreSolar bms-firmware](https://github.com/LibreSolar/bms-firmware)：LibreSolar 是 BQ769x2 + 整板教材；本仓是 **DVC1124 + 可插拔框架 + 工具链入口**，串数叙事可到 24S。

## 仓结构

```
geekbms-fw/
├── LICENSE                 # Apache-2.0
├── README.md
├── SECURITY.md
├── docs/                   # 架构、Roadmap、AFE API RFC、DVC1124 寄存器笔记、安全
├── afe/
│   ├── include/afe_driver.h
│   └── dvc1124/            # 首发驱动 stub
├── core/                   # 保护状态机等
├── hal/stm32/              # I2C / UART stub
├── apps/demo_16s/          # 16S 演示应用说明
└── tools/                  # 寄存器 dump / YAML 参数
```

## v0.1 范围

| 交付 | 说明 |
|------|------|
| AFE 接口冻结 | 见 [`docs/afe_driver_rfc.md`](docs/afe_driver_rfc.md) |
| DVC1124 读写路径 | 按公开 DS；未公开寄存器地址标 TBD，不臆造 |
| 保护状态机最小集 | OV/UV/OC/SCD 占位 + 高边 FET 叙事 |
| 串数可配 5–24S | demo 默认 16S |
| UART 文本遥测 | CSV/JSON 一行 |
| 主机工具入口 | dump + YAML/JSON 参数 |
| CI（后续周） | 编译 + 寄存器打包单元测 |

详见 [`docs/roadmap.md`](docs/roadmap.md)。

## 芯片事实边界

- DVC1124 有公开数据手册：[DVC1124 数据手册 V0.6 (PDF)](https://bms.pub/uploads/soft/Datasheet/DVC1124%E6%95%B0%E6%8D%AE%E6%89%8B%E5%86%8C_V0.6.pdf)。
- 「达锂 / JBD / 蚂蚁等大厂在用」属圈内传闻，公开源未证实——文档与推广**禁止**写「大厂标配」。
- 寄存器 **地址映射**以原厂 DS 为准；本仓笔记中凡未在公开摘录中确认偏移的条目一律 **TBD**。

## 快速开始（W1）

本周交付为**仓骨架 + 文档 + API RFC + stub**，尚无完整可链接的 STM32 工程。W2 起补 I²C 真读写与假设备层。

```bash
# 本地树已就绪；推送到 GitHub 由维护者完成
ls docs afe core hal apps tools
```

## 许可证

Apache License 2.0 — 见 [`LICENSE`](LICENSE)。

## 链接

- 架构：[`docs/architecture.md`](docs/architecture.md)
- Roadmap：[`docs/roadmap.md`](docs/roadmap.md)
- AFE API RFC：[`docs/afe_driver_rfc.md`](docs/afe_driver_rfc.md)
- DVC1124 寄存器笔记：[`docs/dvc1124_registers.md`](docs/dvc1124_registers.md)
