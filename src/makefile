SOURCES=loader.o kernel.o
CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector

LDFLAGS=-Tlinker.ld
ASFLAGS=-felf

all: $(SOURCES) link

clean:
	-rm kernel $(SOURCES)
link:
	ld $(LDFLAGS) -o kernel $(SOURCES)
.s.o:
	nasm $(ASFLAGS) $<
