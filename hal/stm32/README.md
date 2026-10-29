# HAL: STM32（首发 MCU）

本目录为 **STM32** 平台抽象桩：`hal_i2c` / `hal_uart`。

## W1 状态

- 头文件与 `.c` stub 已就位，返回 `*_ERR_NOTIMPL`。
- **尚未**绑定具体型号（F0/F1/G0/…）或 CubeMX 工程。

## W2 计划

1. 选定一颗评估 MCU（建议带 5 V 容忍 I²C 或合适电平转换）。
2. 100 kHz I²C 主机 + DVC1124 CRC 帧读写。
3. UART 115200 文本遥测。
4. 用 `GEEKBMS_HAS_HAL_I2C` 编译宏连接 `afe/dvc1124`。

内部另有历史 N32 实验代码，**不**作为本公开仓默认端口。
