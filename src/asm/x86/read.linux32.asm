; Reads input from the user then echos it back
; x86 32bit Linux kernel only

SECTION .data
	prompt: db "> ",0
	prompt_len equ $ - prompt

	msg: db "You said: ",0
	msg_len equ $ - msg

	nl: db 10

SECTION .bss
	buf resb 11		; buffer to store text

SECTION .text
	global main

main:
	; write prompt via system_write()
	mov eax, 4
	mov ebx, 1
	mov ecx, prompt
	mov edx, prompt_len
	int 0x80

	; read and store import via system_read()
	mov eax, 3		; system_read
	mov ebx, 2		; stdin
	mov ecx, buf		; buffer to hold text
	mov edx, 11		; buffer size
	int 0x80

	; write reply via system_write()
	mov eax, 4
	mov ebx, 1
	mov ecx, msg
	mov edx, msg_len
	int 0x80

	; write input via system_write()
	mov eax, 4
	mov ebx, 1
	mov ecx, buf
	mov edx, 11
	int 0x80

	; write a new line (\n) via system_write()
	mov eax, 4
	mov ebx, 1
	mov ecx, nl
	mov edx, 1
	int 0x80

	; exit
	mov eax, 1
	mov ebx, 0
	int 0x80

