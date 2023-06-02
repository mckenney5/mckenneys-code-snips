/* Allocates and writes data on the heap */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]){
	const size_t GB = 1000000000;

	char *o = NULL;
	int num = 0;
	if(argv[1] != NULL) num = atoi(argv[1]); //get the number from the user
	if(num <= 0){ //if the number is invalid
		fprintf(stderr, "Invalid number\n");
		return 1;
	}
	printf("Allocating ~%d Gig(s).\nPress ENTER to quit.", num);
	o = malloc((size_t)num*GB * sizeof(char));

	srand(num);
	int r = rand(); //get a random number
	memset(o, (char)r, num*GB*sizeof(char)); //write that rando num to memory
	if(o == NULL){
		perror(" ");
		return 1;
	}
	getc(stdin); //Wait for a user to hit ENTER
	free(o);
	return 0;
}

