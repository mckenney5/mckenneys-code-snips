; Writes 'hello, world' to stdout via puts (glibc)
; x86 32bit only

SECTION .data			; initalized data
	msg: db "Hello, World",0 ; the mesg to display

SECTION .text			; the code
	global main		; main used so gcc can be linker
				; can be changed to _start for ld
	extern puts

main:
	push ebp		; prolog
	mov ebp, esp

	push msg		; push the msg to the stack
	call puts		; calls puts, puts get msg from stack
	;pop msg			; removes msg from stack
	
	mov esp, ebp		; epilog
	pop ebp
	
	ret

