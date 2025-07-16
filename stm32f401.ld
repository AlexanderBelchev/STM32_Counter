/* linker script */

/* Label for the program's entry point */
ENTRY(reset_handler)

/* Define the end of RAM and limit of stack memory */
/* 64KB SRAM (65,536bytes = 0x10000)*/
/* 256KB FLASH */
/* RAM starts at address 0x20000000 */
_estack = 0x20010000;

/* Minimum size for stack and dynamic memory. */
/* An error will be generated if there is
 * less than this much RAM lefover */
/* (1KB) */
_Min_Leftover_RAM = 0x400;

MEMORY
{
    FLASH( rx )         : ORIGIN = 0x08000000, LENGTH = 256K
    RAM ( rxw )         : ORIGIN = 0x20000000, LENGTH = 64K
}

SECTIONS
{
    /* Vector table goes at the start of the flash */
    .vector_table :
    {
        . = ALIGN(4);
        KEEP (*(.vector_table))
        . = ALIGN(4);
    } >FLASH

    /* The 'text' section contains the main program code. */
    .text :
    {
        . = ALIGN(4);
        *(.text)
        *(.text*)
        . = ALIGN(4);
    } >FLASH

    /* The 'rodata' section contains read-only data,
     * constants, strings, information that won't change. */
    .rodata :
    {
        . = ALIGN(4);
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
    } >FLASH

    /* The 'data' section is space set aside in RAM for
     * things like variables, which can change. */
    _sidata = .;
    .data : AT(_sidata)
    {
        . = ALIGN(4);
        /* Mark start and end locations for the 'data' section. */
        _sdata = .;
        *(.data)
        *(.data*)
        _edata = .;
        . = ALIGN(4);
    } >RAM

    /* The 'bss' section is similar to the 'data' section,
     * but its space is initialized to all 0s at the
     * start of the program */
    .bss :
    {
        . = ALIGN(4);
        /* Also mark the start adn end of the BSS section. */
        _sbss = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    } >RAM

    /* Space set aside for the application's heap/stack */
    .dynamic_allocations :
    {
        . = ALIGN(4);
        _ssystem_ram = .;
        . = . + _Min_Leftover_RAM;
        . = ALIGN(4);
        _esystem_ram = .;
    } >RAM
}
