; Reads input from the user then says hello
; x86 32bit Linux kernel only

; to compile: nasm -f elf32 -o test.o assembly.nasm.x32.linux.asm && gcc -m32 -o as32.out test.o

SECTION .data			; read only variables
	prompt: db "Enter your name: ",0
	prompt_len equ $ - prompt

	msg: db "Hello ",0
	msg_len equ $ - msg

	end: db 33, 10, 0	; !\n

SECTION .bss			; variables
	buf resb 1024		; buffer to store text

SECTION .text			; functions
	global main

main:				; start of the program

	; write prompt via system_write()
	mov ecx, prompt		; display the prompt
	mov edx, prompt_len	; prompt's length
	call write		; call the write routine

	; read and store import via system_read()
	mov eax, 3		; system_read
	mov ebx, 2		; stdin
	mov ecx, buf		; buffer to hold text
	mov edx, 1024		; buffer size
	int 0x80		; call the kernel

	; remove the newline char
	call clean		; go to the clean routine

	; write reply via system_write()
	mov ecx, msg		; the reply
	mov edx, msg_len	; the size of the variable
	call write		; display to the screen

	; write input via system_write()
	mov ecx, buf		; what the user typed
	mov edx, 1024		; size of the variable
	call write		; display to the screen

	; write a the end (!\n\0) via system_write()
	mov ecx, end		; "!\n\0"
	mov edx, 3		; size of end
	call write		; display to the screen

	; exit
	mov eax, 1		; system_exit
	mov ebx, 0		; exit without an error (exit code 0)
	int 0x80		; call the kernel so it stops this program

write: 				; displays text on the screen
				; takes the text in ecx and size in edx
	mov eax, 4		; system_write
	mov ebx, 1		; stdout
	int 0x80		; call the kernel
	ret			; return to where we were

clean:				; removes the newline char from input
	mov ecx, buf		; load the input
	jmp .check		; go to the loop section
.next_char:
	add ecx, 1		; go to the next char
.check:
	cmp [ecx], byte 10	; check if the char is a newline (by deref the pointer)
	jnz .next_char		; if its not then go to the next char
	mov [ecx], byte 0	; if it is then replace it with null
	ret			; go back to the main program

