These files allow C to use an ASM function

### Files:
- add10.asm
	- Assembly code of add10
- add10.h
	- Header file so C knows how to use the function
- main.c
	- The C program that calls add10

### Compiling / Assembeling / Linking
`nasm -f elf -o add10.o add10.asm`

`gcc -m32 -o test add10.o main.c`

