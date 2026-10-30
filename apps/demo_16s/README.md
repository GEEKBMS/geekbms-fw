# demo_16s — 16S 电自演示应用

**状态：** W1 仅文档与占位；可编译主程序在 W3。

## 将要做什么

1. 以 **16S** 为默认串数初始化 DVC1124 驱动（框架支持 5–24S）。
2. 周期读取电芯电压 / 保护标志（W2+ 真 I²C；此前可用假设备）。
3. 跑 `core/protect_sm` 最小状态机。
4. 经 UART 输出一行 CSV 遥测（见 `core/telemetry.h`）。
5. **默认不导通** 高边 CHG/DSG，直至显式安全策略与台架确认。

## 非目标

- 不提供量产参数表或「可装车」固件。
- 不含 CAN/BLE。
- 不绑定具体 PCB 网表（评估板征集在 W4）。

## 预期目录（W3）

```
apps/demo_16s/
├── README.md      ← 本文件
├── main.c         ← 待加
├── board.h        ← 引脚与 Rsense
└── CMakeLists.txt 或 Makefile
```

## 安全

接真电池前阅读仓库根目录 `SECURITY.md` 与 `docs/safety.md`。
