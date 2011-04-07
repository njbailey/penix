SOURCES=loader.o kernel.o common.o monitor.o string.o
CFLAGS=-I. -nostdlib -nostdinc -fno-builtin -fno-stack-protector

LDFLAGS=-Tlinker.ld
ASFLAGS=-felf

all: $(SOURCES) link

clean:
	-rm kernel $(SOURCES)
link:
	ld $(LDFLAGS) -o kernel $(SOURCES)
.s.o:
	nasm $(ASFLAGS) $<
