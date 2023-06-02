/*
 * The C programming language
 * Takes in an ending number then does fizzbuzz
 * to compile: gcc c.c -o c
*/

#include <stdio.h> // include the standard io library for 'printf' and 'fgets'
#include <stdlib.h> // allows: atol

int main(void){
	// display prompt
	printf("Insert end point: ");

	// get the name
	char input[1024] = {'\0'};
	fgets(input, 1024, stdin);

	// convert input to a number
	long end = 0;
	end = atol(input);

	// set up a for loop
	long i = 0;
	for(i = 1; i <= end; i++){
	// set i to 1, while i is less than or equal to end, add 1 to i
		if(i % 15 == 0) //if i is divisable by 15
			puts("fizzbuzz");
		else if(i % 3 == 0)
			puts("fizz");
		else if(i % 5 == 0)
			puts("buzz");
		else
			printf("%ld\n", i);
	}

	// exit normally
	return EXIT_SUCCESS;
}

