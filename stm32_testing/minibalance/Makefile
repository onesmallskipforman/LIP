
SRCS := $(shell find ./ -mindepth 2 -type f -name '*.c' ! -path './BALANCE/MPU6050/*' ! -path './BALANCE/DMP/*' ! -path './BALANCE/DataScope_DP/*')
SRCS += syscalls.c
OBJS := $(SRCS:%.c=out/%.o)
HDRS := $(shell find ./ -type f -name '*.h')
INC_DIRS := $(shell find ./ -mindepth 1 -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
ASMS := startup_stm32f103xb.s

# %.o: %.c
#	echo $@ $^
#	echo $(OBJS)

out/%.o: %.c
	mkdir -p $(@D)
	arm-none-eabi-gcc -o $@ -c $(INC_FLAGS) -DSTM32F10X_MD -g -nostdlib -mcpu=cortex-m3 -mthumb $^

# -x assembler-with-cpp
out/%.o: %.s
	arm-none-eabi-gcc  -o $@ -c -g -nostdlib -mcpu=cortex-m3 -mthumb $^


# $(info $(SRCS))

# minibalance_lib: $(OBJS)
#	ar rcs libminibalance.a $^

out/minibalance.elf: $(OBJS) $(ASMS)
	arm-none-eabi-gcc $^ -lc -lgcc -lm -o $@ -Wl,-TSTM32F103XB_FLASH.ld -nostartfiles -nostdlib -mthumb

out/minibalance.bin: minibalance.elf
	arm-none-eabi-objcopy -O binary $^ $@

# -mthumb needed for __libc_init_array
out/application.elf: main.o syscalls.o startup_stm32f103xb.o
	arm-none-eabi-gcc \
		$^ -lc -lgcc -lm -o $@ \
		-Wl,-TSTM32F103XB_FLASH.ld \
		-nostartfiles -nostdlib \
		-mthumb

application.bin: application.elf
	arm-none-eabi-objcopy -O binary $^ $@

application.hex: application.elf
	arm-none-eabi-objcopy -O ihex $^ $@

load: application.hex
	sudo chown skipper /dev/ttyUSB0
	STM32_Programmer_CLI -c port=/dev/ttyUSB0 -d $^ -v # --start

run: load
	sudo chown skipper /dev/ttyUSB0
	STM32_Programmer_CLI -c port=/dev/ttyUSB0 --start

clean:
	rm -rf out *.o *.elf *.bin *.hex
