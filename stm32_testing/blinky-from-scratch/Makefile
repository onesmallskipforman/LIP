main.o: main.c
	arm-none-eabi-gcc -o main.o -c -g -nostdlib -mcpu=cortex-m3 -mthumb main.c

syscalls.o: syscalls.c
	arm-none-eabi-gcc -o syscalls.o -c -g -nostdlib -mcpu=cortex-m3 -mthumb syscalls.c

startup_stm32f103xb.o: startup_stm32f103xb.s
	arm-none-eabi-gcc -x assembler-with-cpp -o startup_stm32f103xb.o -c -g -nostdlib -mcpu=cortex-m3 -mthumb startup_stm32f103xb.s

application.elf: main.o syscalls.o link.ld startup_stm32f103xb.o
	arm-none-eabi-gcc \
		main.o syscalls.o startup_stm32f103xb.o \
		-lc -lgcc -lm \
		-o application.elf \
		-Wl,-TSTM32F103XB_FLASH.ld \
		-nostartfiles -nostdlib \
		-mthumb # keeps __libc_init_array working

application.bin: application.elf
	arm-none-eabi-objcopy -O binary application.elf application.bin

application.hex: application.elf
	arm-none-eabi-objcopy -O ihex application.elf application.hex

clean:
	rm -rf *.o *.elf *.bin *.hex
