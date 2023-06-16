; Hello World using system calls
; for x86_64 Linux only

section .data				; constants
	text db "Hello, World",10	; const char* Hello World

section .text				; function declaring
	global main			; used for gcc

main:					; start
	mov rax, 1			; sys_write
	mov rdi, 1			; write to STDOUT
	mov rsi, text			; pointer to text
	mov rdx, 14			; text length
	syscall				; sys_write(STDOUT, text&, size_of(text));
	
	mov rax, 60			; call sys_exit
	mov rdi, 0			; exit with error code 0
	syscall				; sys_exit(0)

