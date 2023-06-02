/* calculates factorials recursively */
#include <stdio.h>
#include <stdlib.h>
unsigned long long factorial(const unsigned long num){
/* Factorial is n * (n!-1) */
	if(num == 0)
		return 1;
	else
		return (num * factorial(num-1)); //calls the function recursively
}

int main(int argc, char *argv[]){
	if(argc == 2 && atol(argv[1]) >= 0){
		//Display the answer to the screen in #!=# format
		printf("%s! = %llu\n", argv[1], factorial((unsigned) atol(argv[1])));
		return EXIT_SUCCESS;
	} else {
		//Exits if the user does not provide a number
		printf("Usage: %s <unsigned-number>\n", argv[0]);
		return EXIT_FAILURE;
	}
}

