%.o: %.c
	arm-none-eabi-gcc -o $@ -c -g -nostdlib -mcpu=cortex-m3 -mthumb $^

# -x assembler-with-cpp
%.o: %.s
	arm-none-eabi-gcc  -o $@ -c -g -nostdlib -mcpu=cortex-m3 -mthumb $^

# -mthumb needed for __libc_init_array
application.elf: main.o syscalls.o startup_stm32f103xb.o
	arm-none-eabi-gcc \
		$^ -lc -lgcc -lm -o $@ \
		-Wl,-TSTM32F103XB_FLASH.ld \
		-nostartfiles -nostdlib \
		-mthumb

application.bin: application.elf
	arm-none-eabi-objcopy -O binary $^ $@

application.hex: application.elf
	arm-none-eabi-objcopy -O ihex $^ $@

clean:
	rm -rf *.o *.elf *.bin *.hex
