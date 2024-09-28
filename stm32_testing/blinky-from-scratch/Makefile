main.o: main.c
	arm-none-eabi-gcc -o main.o -c -g -nostdlib -mcpu=cortex-m3 -mthumb main.c

startup_stm32f103xb.o: startup_stm32f103xb.s
	arm-none-eabi-gcc -o startup_stm32f103xb.o -c -g -nostdlib -mcpu=cortex-m3 -mthumb startup_stm32f103xb.s

application.elf: main.o link.ld startup_stm32f103xb.o
	# TODO: see step-4 and step-5
	# arm-none-eabi-gcc -o application.elf -Wl,-TSTM32F103XB_FLASH.ld -Wl,--gc-sections --specs=nano.specs -lc -lgcc startup_stm32f103xb.o main.o
	arm-none-eabi-gcc -o application.elf -Wl,-Tlink.ld -nostartfiles main.o

application.bin: application.elf
	arm-none-eabi-objcopy -O binary application.elf application.bin

application.hex: application.elf
	arm-none-eabi-objcopy -O ihex application.elf application.hex

clean:
	rm -rf *.o *.elf *.bin *.hex
