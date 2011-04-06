CC=gcc
CFLAGS=-I.

OBJECTS=loader.o kernel.o

all: main

main: ${OBJECTS}

kernel.o:
	gcc -o kernel.o -c kernel.c -Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs

loader.o:
	nasm -f elf -o loader.o loader.asm
