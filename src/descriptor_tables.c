// descriptor_tables.c - Initialises the GDT and IDT, and defines the
// default ISR and IRQ handler.

#include <descriptor_tables.h>

// Lets us access our ASM functions from here.
extern void gdt_flush(u32int);

// internal function prototypes.
static void init_gdt(void);
static void gdt_set_gate(s32int, u32int, u32int, u8int, u8int);

gdt_entry_t gdt_entries[5];
gdt_ptr_t   gdt_ptr;
//idt_entry_t idt_entries[256];
//idt_ptr_t   idt_ptr;

void init_descriptor_tables(void)
{
	init_gdt();
}

static void init_gdt()
{
	gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
	gdt_ptr.base  = (u32int) &gdt_entries;

	gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

	gdt_flush((u32int)&gdt_ptr);
}

// Set the value of one GDT entry
static void gdt_set_gate(s32int num, u32int base, u32int limit, u8int access, u8int gran)
{
	gdt_entries[num].base_low    = (base & 0xFFFF);
	gdt_entries[num].base_middle = (base >> 16) & 0xFF;
	gdt_entries[num].base_high   = (base >> 24) & 0xFF;

	gdt_entries[num].limit_low   = (limit & 0xFFFF);
	gdt_entries[num].granularity = (limit >> 16) & 0x0F;

	gdt_entries[num].granularity |= gran & 0xF0;
	gdt_entries[num].access      = access;
}
