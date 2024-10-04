
SRCS := $(shell find ./ -mindepth 2 -type f -name '*.c' ! -path './BALANCE/MPU6050/*' ! -path './BALANCE/DMP/*' ! -path './BALANCE/DataScope_DP/*')
SRCS += syscalls.c
OBJS := $(SRCS:%.c=OBJ/%.o) OBJ/startup_stm32f103xb.o
HDRS := $(shell find ./ -type f -name '*.h')
INC_DIRS := $(shell find ./ -mindepth 1 -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

OBJ/%.o: %.c
	mkdir -p $(@D)
	arm-none-eabi-gcc -o $@ -c $(INC_FLAGS) -DSTM32F103xB -g -nostdlib -mcpu=cortex-m3 -mthumb $<

# -x assembler-with-cpp
OBJ/%.o: %.s
	mkdir -p $(@D)
	arm-none-eabi-gcc  -o $@ -c -g -nostdlib -mcpu=cortex-m3 -mthumb $<

# $(info $(OBJS))

# minibalance_lib: $(OBJS)
#	arm-none-eabi-ar rcs libminibalance.a $^

# -mthumb needed for __libc_init_array
minibalance.elf: $(OBJS)
	mkdir -p $(@D)
	arm-none-eabi-gcc --specs=nosys.specs --specs=nano.specs $^ -lc -lgcc -lm -o $@ -Wl,-TSTM32F103XB_FLASH.ld -nostartfiles -nostdlib -mcpu=cortex-m3 -mthumb

minibalance.bin: minibalance.elf
	arm-none-eabi-objcopy -O binary $< $@

minibalance.hex: minibalance.elf
	arm-none-eabi-objcopy -O ihex $< $@

load: minibalance.hex
	sudo chown skipper /dev/ttyUSB0
	STM32_Programmer_CLI -c port=/dev/ttyUSB0 -d $< -v # --start

run: load
	sudo chown skipper /dev/ttyUSB0
	STM32_Programmer_CLI -c port=/dev/ttyUSB0 --start

clean:
	rm -rf OBJ/* *.elf *.bin *.hex
