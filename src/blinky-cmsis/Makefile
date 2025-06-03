%.o: %.c
	arm-none-eabi-gcc -o $@ -DSTM32F103xB -c -g -nostdlib -mcpu=cortex-m3 -mthumb $^

# -x assembler-with-cpp
%.o: %.s
	arm-none-eabi-gcc  -o $@ -DSTM32F103xB -c -g -nostdlib -mcpu=cortex-m3 -mthumb $^

# -mthumb needed for __libc_init_array
application.elf: main.o syscalls.o startup_stm32f103xb.o
	arm-none-eabi-gcc -DSTM32F103xB \
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

compile_commands.json: clean
	bear -- $(MAKE) $(OBJS)

clean:
	rm -rf ./compile_commands.json OBJ/* *.elf *.bin *.hex
