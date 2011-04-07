// monitor.c --

#include <monitor.h>

static u16int* video_memory;
static u8int cursor_x;
static u8int cursor_y;

static void move_cursor(void)
{
	u16int cursor_location = cursor_y * 80 + cursor_x;

	outb(0x3D4, 14);                   // Tell the VGA board we are setting the high cursor byte.
	outb(0x3D5, cursor_location >> 8); // Send the high cursor byte
	outb(0x3D4, 15);                   // Tell the VGA board we are setting the low cursor byte.
	outb(0x3D5, cursor_location);      // Send the low cursor byte.
}

static void scroll(void)
{
	// Get a space character with the default color attributes.
	u8int attribute_byte = (0 << 4) | (15 & 0x0F);
	u16int blank = 0x20 | (attribute_byte << 8);

	// Row 25 is the end, this means we need to scroll up.
	if(cursor_y >= 25)
	{
		// Move the current text chunk that makes up the screen
		// back in the buffer by a line
		int i;

		for(i = 0; i < 24 * 80; i++)
		{
			video_memory[i] = video_memory[i + 80];
		}

		// The last line should now be blank.  Do this by writing
		// 80 spaces to it.
		for(i = 24 * 80; i < 25 * 80; i++)
		{
			video_memory[i] = blank;
		}

		// The cursor should now be on the last line.
		cursor_y = 24;
	}
}

void monitor_init(void)
{
	video_memory = (u16int*) 0xb8000; // TODO: make it so we determine if it starts at 0xB8000 or 0xB0000
	cursor_x = 0;
	cursor_y = 0;
}

void monitor_put(char c)
{
	u8int back_color = 0;  // Black
	u8int fore_color = 15; // White

	// The attribute byte is made up of two nibbles -- the lower being the
	// foreground color, and the upper being the background color.
	u8int attribute_byte = (back_color << 4) | (fore_color & 0x0f);

	// The attribute byte is the top 8 bits of the word we have to send to the
	// VGA board.
	u16int attribute = attribute_byte << 8;
	u16int* location;

	// Handle a backspace by moving the cursor back one space, if applicable.
	if(c == 0x08 && cursor_x > 0)
	{
		cursor_x--;
	}

	// Handle a tab by increasing the cursor's X, but only to a point
	// where it is divisible by 8.
	else if(c == 0x09)
	{
		cursor_x = (cursor_x + 8) & ~(8 - 1);
	}

	// Handle a carriage return
	else if(c == '\r')
	{
		cursor_x = 0;
	}

	// Handle a newline by moving the cursor back to the left and increasing the row.
	else if(c == '\n')
	{
		cursor_x = 0;
		cursor_y++;
	}
	else if(c >= ' ')
	{
		location = video_memory + (cursor_y * 80 + cursor_x);
		*location = c | attribute;
		cursor_x++;
	}

	// Check if we need to insert a new line because we have reached the end
	// of the screen.
	if(cursor_x >= 80)
	{
		cursor_x = 0;
		cursor_y++;
	}
	
	scroll();
	move_cursor();
}

// Clears the screen by copying lots of spaces to the framebuffer.
void monitor_clear(void)
{
	// Make an attribute byte for the default colors.
	u8int attribute_byte = (0 << 4) | (15 & 0x0F);
	u16int blank = 0x20 | (attribute_byte << 8);
	
	int i;
	for(i = 0; i < 80 * 25; i++)
	{
		video_memory[i] = blank;
	}

	cursor_x = 0;
	cursor_y = 0;
	move_cursor();
}

// outputs a null-terminated ASCII string to the monitor.
void monitor_write(const char* str)
{
	int x = 0;
	
	while(str[x])
	{
		monitor_put(str[x++]);
	}
}

void monitor_write_dec(u32int value)
{
	u8int result[11];
	s8int i = 0;

	if (value == 0) {
		monitor_put ('0');
		return;
	}

	while(value > 0) {
		result[i] = value % 10;
		result[i++] += '0';
		value /= 10;
	}

	while(i >= 0)
		monitor_put(result[i--]);
}

void monitor_write_hex(u32int value)
{
	u8int result[11];
	s8int i = 0;

	if(value == 0) {
		monitor_write("0x0");
		return;
	}

	while(value > 0)
	{
		result[i] = value % 16;
		result[i] += (result[i] < 10 ? '0' : '7');
		value /= 16;
		i++;
	}

	monitor_write("0x");
	
	while(i >= 0)
		monitor_put(result[i--]);
}
