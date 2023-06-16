; Writes msg X times
; x86 32bit Linux kernel only

SECTION .data			; initalized data
	msg: db "Hi",10,0 	; the mesg to display
	msg_len equ $ - msg 	; msg's length

SECTION .text			; the code
	global main		; main used so gcc can be linker
				; can be changed to _start for ld

main:
	push ebp		; prolog
	mov ebp, esp

	mov ecx, 10 		; loop for 10 times (i=10)

L1:				; for(i=10; i > 0; i--)
	push ecx		; save the loop counter (int i)
	mov ecx, msg		; display hi
	mov edx, msg_len	; with len of 4
	call write		; sys_call write(msg, len)
	
	pop ecx			; retreive loop counter (i)
	loop L1			; loop
	; end of loop
	call done		; exit

write:
	; write(msg, len)
	;       ecx, edx

	push ebp		; prolog
	mov ebp, esp
	
	mov eax, 4		; sys_call write
	mov ebx, 1		; stdout
	int 0x80		; call kernel
	
	mov esp, ebp		; epilog
	pop ebp
	ret

done:
	; Revert stack pointer to the base
	; Then tell the kernel that we are done
	mov esp, ebp
	pop ebp
	mov eax, 1
	mov ebx, 0
	int 0x80
	ret

