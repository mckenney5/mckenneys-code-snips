; Adds 10 to a provided number
; Requires a C header file to be called by C
; x86 32bit only

SECTION .text
	global add10

add10:
	; C equiv:
	; 	int add10(int num){
	;		num = num+10;
	;		return num;
	;	}

	push ebp	 ; prolog
	mov ebp, esp
	
	mov eax, [ebp+8] ; get the arg
	add eax, 10	 ; add 10 to provided arg

	mov esp, ebp
	pop ebp
	ret		 ; return to the caller

