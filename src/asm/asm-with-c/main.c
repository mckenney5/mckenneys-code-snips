#include <stdio.h>	/* printf */
#include "add10.h"	/* add10 (our ASM function) */
int main(void){
	int num = 0;
	printf("Original: '%d' ", num);
	num = add10(num); //call add10(0) and save the return val to num
	printf("| Now: '%d'\n", num);
	return 0;
}

