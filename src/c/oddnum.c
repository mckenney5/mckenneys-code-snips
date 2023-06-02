/* Takes user input of two numbers and finds all the odd numbers between them */

#include <stdio.h> //used to display text on the screen (fprintf, printf, puts)
#include <stdlib.h> //used for converting user input to numbers (atoll)

int main(int argc, char *argv[]){
	long long i = 0;

	//check if syntax is correct
	if(argc != 3){
		fprintf(stderr, "Syntax Error: usage '%s <start> <end>'\n", argv[0]);
		return EXIT_FAILURE;
	}

	//grab values, if the user enters a char, it is changed to zero
	long long start = atoll(argv[1]);
	long long end = atoll(argv[2]);
	printf("Listing odd numbers from %lld to %lld.\n", start, end);

	//check if we're counting up or down, then do it
	if(start > end){
		if(start%2 == 0)
			i = start-1;
		else
			i = start;
	
		for (i; i >= end; i -= 2)
			printf("%lld ", i);
	} else {
		if(start%2 == 0)
			i = start+1;
		else
			i = start;
		
		for (i; i <= end; i += 2)
			printf("%lld ", i);
	}
	puts(" ");
	return EXIT_SUCCESS;
}

