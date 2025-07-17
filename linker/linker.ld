ENTRY(Reset_Handler)

/* Describe the taget's MEMORY zones 
 * The linker usit to relocation (mem addressing)
 * */
MEMORY
{
	FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 1048576
	RAM (rwx)  : ORIGIN = 0x20000000, LENGTH = 262144
}

/* Create MEMORY sections in the ELF out file
 * define the order of these sections and in wich MEMORY zone to place a section
 * */
SECTIONS
{
	.text :
	{
		/* Merge all .isr_vector of all input files. etc..*/
		*(.isr_vector)
		*(.text)
		*(.rodata)
		. = ALIGN(4);
		_etext = .;
		/* Store the updated location counter value for */
        /* ‘_etext’ symbol.								*/
	}> FLASH

	_la_data = LOADADDR(.data);
	/* store the lma of .data start for the Reset_Handler */

	.data :
	{
		_sdata = .;
		*(.data)
		. = ALIGN(4);
		_edata = .;
	}> RAM AT> FLASH
	/* > (vma) AT> (lma) */
	/* virtual memory address (final dest)*/
	/* load memory address */

	.bss :
	{
		_sbss = .;
		*(.bss)
		. = ALIGN(4);
		_ebss = .;
	}> RAM
}
