# Host smoke build (no STM32 SDK). W1 sanity only.
CC ?= gcc
CFLAGS ?= -std=c11 -Wall -Wextra -Werror -DGEEKBMS_HOST_SMOKE
INCLUDES = -Iafe/include -Iafe/dvc1124 -Icore -Ihal/stm32

SRCS = \
	afe/dvc1124/afe_dvc1124.c \
	core/protect_sm.c \
	core/telemetry.c \
	apps/demo_16s/main.c

.PHONY: smoke clean

smoke:
	mkdir -p build
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) -o build/demo_16s_host
	./build/demo_16s_host

clean:
	rm -rf build
