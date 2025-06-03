# CFLAGS  ?=  -DSTM32F103xB \
#			-W -Wall -Wextra -Wundef -Wshadow -Wdouble-promotion \
#             -Wformat-truncation -fno-common -Wconversion \
#             -g3 -Os -ffunction-sections -fdata-sections \
#			-I./Core/Inc \
#			-I./Drivers/CMSIS/Device/ST/STM32F1xx/Include \
#			-I./Drivers/STM32F1xx_HAL_Driver/Inc \
#			-I./Drivers/CMSIS/Include \
#			-I./Hardware/OLED \
#             -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -mfpu=fpv4-sp-d16 $(EXTRA_CFLAGS)




CFLAGS  ?=  -DSTM32F103xB \
			-W -Wall -Wextra -Wundef -Wshadow -Wdouble-promotion \
            -Wformat-truncation -fno-common -Wconversion \
            -g3 -Os -ffunction-sections -fdata-sections \
			-I./Core/Inc \
			-I./Drivers/CMSIS/Device/ST/STM32F1xx/Include \
			-I./Drivers/STM32F1xx_HAL_Driver/Inc \
			-I./Drivers/CMSIS/Include \
			-I./Hardware/OLED \
            -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -mfpu=fpv4-sp-d16 $(EXTRA_CFLAGS)






LDFLAGS ?= -TSTM32F103C8TX_FLASH.ld --specs=nosys.specs -Wl,-Map=$@.map -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group

# SOURCES = system_stm32f1xx.c gcc_startup_stm32f103xb.s main.c
SOURCES ?= $(wildcard ./Core/Src/*.c) $(wildcard ./Core/Startup/*.s)

RM = rm -f

build: firmware.bin

firmware.elf: $(SOURCES)
	arm-none-eabi-gcc $(SOURCES) $(CFLAGS) $(LDFLAGS) -o $@

firmware.bin: firmware.elf
	arm-none-eabi-objcopy -O binary $< $@

flash: firmware.bin
	st-flash --reset write $< 0x8000000

clean:
	$(RM) firmware.*
