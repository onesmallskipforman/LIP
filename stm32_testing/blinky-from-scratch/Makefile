main.o: main.c
	arm-none-eabi-gcc -o main.o -c -g -mcpu=cortex-m3 -mthumb main.c

application.elf: main.o link.ld
	arm-none-eabi-gcc -o application.elf -Wl,-Tlink.ld -nostartfiles main.o

application.bin: application.elf
	arm-none-eabi-objcopy -O binary application.elf application.bin

application.hex: application.elf
	arm-none-eabi-objcopy -O ihex application.elf application.hex

clean:
	rm -rf *.o *.elf *.bin *.hex
