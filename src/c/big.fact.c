/* Uses libgmp10-dev to make bignums */
/* Compile with: gcc -I /sw/include/ -L/sw/lib big.fact.c -lgmp */
#include "gmp.h"
#include <stdio.h>
#include <stdlib.h>

void factorial(const long long n){
	if(n < 0){
		fprintf(stderr, "Number cannot be negative.\n");
		return;
	}

	size_t i;
	mpz_t bn;			/* pointer to gpms internal data structure */

	mpz_init_set_ui(bn,1); 		/* sets bn to 1 (aka initalizes it to 1) */
	for (i=1; i <= n ; ++i)
		mpz_mul_ui(bn,bn,i); 	/* bn = bn * i */
	printf ("%lld! = ", n);
	mpz_out_str(stdout,10,bn);	/* internal function to print the big num to the screen */
	mpz_clear(bn);			/* aka free(bn); */
	putchar('\n');
}

int main(int argc, char * argv[]){
	if (argc != 2)
		printf ("Usage: %s <number>\n", argv[0]);
	else
		factorial(atoll(argv[1]));
	return 0;
}

