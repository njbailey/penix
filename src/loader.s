;
; boot.asm -- Kernel start location.  Also defines multiboot header
; Based on Barn's kernel development tutorial file start.asm
;

MBOOT_PAGE_ALIGN   equ 1 << 0     ; Load kernel and modules on a page boundary
MBOOT_MEM_INFO     equ 1 << 1     ; Provide our kernel with memory info
MBOOT_HEADER_MAGIC equ 0x1BADB002 ; Multiboot Magic Value

; Note: We do not use MBOOT_AOUT_KLUDGE.  It means that GRUD does not
; pass us a symbol table
MBOOT_HEADER_FLAGS equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM     equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

[BITS 32]                         ; All instructions should be 32-bit

[GLOBAL mboot]                    ; Make 'mboot' accessible from C.
[EXTERN code]                     ; Start of the '.text' section.
[EXTERN bss]                      ; Start of the .bss section.
[EXTERN end]                      ; End of the last loadable section.

mboot:
  dd MBOOT_HEADER_MAGIC           ; GRUB will search for this value on each
                                  ; 4-byte boundary in our kernel file
  dd MBOOT_HEADER_FLAGS           ; How GRUB should load our file / settings
  dd MBOOT_CHECKSUM               ; To ensure that the above values are correct

  dd mboot                        ; Location of this descriptor
  dd code                         ; Start of kernel '.text' (code) section
  dd bss                          ; End of kernel '.data' section.
  dd end                          ; End of kernel.
  dd start                        ; This is the entry point of our C code

[GLOBAL start]
[EXTERN kernel_main]

[GLOBAL gdt_flush]                ; Allows the C code to call gdt_flush()
gdt_flush:
	mov eax, [esp + 4]              ; Get the pointer to the GDT, passed as a parameter
	lgdt [eax]                      ; Load the new GDT pointer

	mov ax, 0x10                    ; 0x10 is the offset in the GDT to our data segment
	mov ds, ax                      ; Load all data segment selectors
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:.flush                 ; 0x08 is the offset to our code segment: Far jump!

.flush:
	ret

start:
  push ebx                        ; Load multiboot header location
  
  ; Execute the kernel:
  cli                             ; Disable interrupts
  call kernel_main                ; call our kernel_main() function.
  jmp $                           ; Enter an infinite loop, to stop the processor
                                  ; executing whatever rubbish is in the memory
                                  ; after our kernel.   
