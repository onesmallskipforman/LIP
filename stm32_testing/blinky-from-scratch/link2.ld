ENTRY(_reset)
MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 128K
    RAM (rwx)  : ORIGIN = 0x20000000, LENGTH = 20K
}
_reset_stack_pointer = ORIGIN(RAM) + LENGTH(RAM);

SECTIONS {
  .vectors  : { KEEP(*(.vectors)) }   > FLASH
  .text     : { *(.text*) }           > FLASH
  .rodata   : { *(.rodata*) }         > FLASH

  .data : {
    _sdata = .;   /* .data section start */
    *(.first_data)
    *(.data SORT(.data.*))
    _edata = .;  /* .data section end */
  } > RAM AT > FLASH
  _sidata = LOADADDR(.data);

  .bss : {
    _sbss = .;              /* .bss section start */
    *(.bss SORT(.bss.*) COMMON)
    _ebss = .;              /* .bss section end */
  } > RAM

  . = ALIGN(8);
  _end = .;     /* for cmsis_gcc.h  */
}
