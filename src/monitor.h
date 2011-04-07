// monitor.h -- Defines the interface for monitor.h

#ifndef MONITOR_H
#define MONITOR_H

#include <common.h>

// Initialise the monitor.  Be sure to call this before you use any
// functions for the monitor.
void monitor_init(void);

// Write a single character to the monitor.
void monitor_put(char c);

// Clear the screen to all black.
void monitor_clear(void);

// Output a null-terminated ASCII string to the montior.
void monitor_write(const char*str);

// Output a digit to the monitor.
void monitor_write_dec(u32int value);

// Output a digit to the monitor as a hexadecimal string.
void monitor_write_hex(u32int value);
#endif // MONITOR_H
