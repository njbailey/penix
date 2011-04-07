// kernel.c -- Defines the C-code kernel entry point, calls initialisation routines.
// Made from a reference to JamesM's tutorial.

#include <monitor.h>

int kernel_main(struct multiboot_header* mboot_ptr)
{
	// All our initialisation calls will go in here.
	monitor_init();
	monitor_clear();
	monitor_write("Hello, World!\r\n");
	monitor_write_dec(12345678);
	monitor_put('\n');
	monitor_write_hex(0xCAFEBABE); // loljava
	
	return 0xDEADBABA;
}
