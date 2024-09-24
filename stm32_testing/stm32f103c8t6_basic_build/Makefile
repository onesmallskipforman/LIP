CFLAGS  ?=  -DSTM32F103xB \
			-W -Wall -Wextra -Werror -Wundef -Wshadow -Wdouble-promotion \
            -Wformat-truncation -fno-common -Wconversion \
            -g3 -Os -ffunction-sections -fdata-sections -I. \
            -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -mfpu=fpv4-sp-d16 $(EXTRA_CFLAGS)
LDFLAGS ?= -Tlink.ld -nostartfiles -nostdlib --specs nano.specs -lc -lgcc -Wl,--gc-sections -Wl,-Map=$@.map
SOURCES = gcc_startup_stm32f103xb.s main.c

RM = rm -f

build: firmware.bin


startup.o: gcc_startup_stm32f103xb.s
	arm-none-eabi-gcc -mcpu=cortex-m3 -g3 -DDEBUG \
		-c \
		-x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" \
		--specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

main.o: main.c
	arm-none-eabi-gcc "$<" \
		-mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB \
		-c \
		-I. \
		-O0 -ffunction-sections -fdata-sections -Wall -fstack-usage \
		-MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" \
		--specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

# NOTE: use -DUSE_HAL_DRIVER to switch to hal
system.o: system_stm32f1xx.c
	arm-none-eabi-gcc "$<" \
		-mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG \
		-DSTM32F103xB \
		-c \
		-I. \
		-O0 -ffunction-sections -fdata-sections -Wall -fstack-usage \
		-MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" \
		--specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

firmware.elf: main.o startup.o system.o
	arm-none-eabi-gcc \
		-o "$@" $< \
		-mcpu=cortex-m3 -TSTM32F103XB_FLASH.ld --specs=nosys.specs \
		-Wl,-Map="$@.map" -Wl,--gc-sections -static \
		--specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm \
		-Wl,--end-group

firmware.bin: firmware.elf
	arm-none-eabi-objcopy -O binary $< $@

flash: firmware.bin
	st-flash --reset write $< 0x8000000

clean:
	$(RM) *.elf *.bin *.o *.d
