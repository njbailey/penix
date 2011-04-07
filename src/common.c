// common.c -- Defines some global functions.

#include <common.h>

// Write a byte out to the specified port
void outb(u16int port, u8int value)
{
	asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

// Retrieve a byte from the specified port
u8int inb(u16int port)
{
	u8int ret;
	asm volatile ("inb %1, %0" : "=a" (ret) : "dN" (port));
	return ret;
}

// Retrieve a word from the specified port.
u16int inw(u16int port)
{
	u16int ret;
	asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
	return ret;
}
