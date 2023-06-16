; TODO
; Reads input from the user then says hello
; x86_64 64bit Linux kernel only

; to compile: 
; to link: 

SECTION .data			; read only variables
	prompt: db "Enter your name: ",0
	prompt_len equ $ - prompt

	msg: db "Hello ",0
	msg_len equ $ - msg

	end: db 33, 10, 0	; !\n

SECTION .bss			; variables
	buf resb 21		; buffer to store text

SECTION .text			; functions
	global main

main:				; start of the program

	; write prompt via system_write()

