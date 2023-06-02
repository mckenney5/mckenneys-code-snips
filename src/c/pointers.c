/* creates a var named example, and a var p that stores the address of example, then displays available info */
#include <stdio.h>
int main(){
	long example = 100;
	long *p = NULL;
	p = &example;
	printf("example = '%ld' | p = '%ld' | *p = '%ld'\n", example, p, *p);
	return 0;
}
