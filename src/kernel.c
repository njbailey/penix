// kernel.c -- Defines the C-code kernel entry point, calls initialisation routines.
// Made from a reference to JamesM's tutorial.

int kernel_main(struct multiboot_header* mboot_ptr)
{
  // All our initialisation calls will go in here.
  return 0xDEADBABA;
}
