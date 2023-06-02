; Writes hello, world to stdout via linux sys_calls
; x86 32bit Linux kernel only

SECTION .data			; initalized data
	msg: db "Hello, World",10,0 	; the mesg to display
	msg_len equ $ - msg 	; msg's length

SECTION .text			; the code
	global main		; main used so gcc can be linker
				; can be changed to _start for ld

main:
	push ebp		; prolog
	mov ebp, esp

	push msg_len		; add the msg length to the stack
	push msg		; add the msg to the stack
	call sys_write		; sys_call write(msg, len)
	
	call done		; clean up and exit

sys_write:
	push ebp		; prolog
	mov ebp, esp

	; stack: [length][msg][return_addr][old ebp]*
	
	mov ecx, [ebp + 8]	; get msg from stack
	mov edx, [ebp + 12]	; get msg_len from stack
	mov eax, 4		; sys_call write
	mov ebx, 1		; stdout
	int 0x80		; call kernel
	
	mov esp, ebp		; epilog
	pop ebp
	ret

done:
	; Revert stack pointer to the base
	; Then tell the kernel that we are done

	mov esp, ebp		; epilog
	pop ebp

	mov eax, 1		; sys_call exit
	mov ebx, 0		; exit(0);
	int 0x80		; call the kernel
	ret

