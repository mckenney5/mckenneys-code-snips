/* uses a case statement to check if the input starts with an 'a' or a 'b' */
#include <stdio.h>
int main(int argc, char *argv[]){
	if(argc != 2){
		fprintf(stderr, "Usage: %s <string>\n", argv[0]);
		return 1;
	}

	switch(argv[1][0]){
		case 'a':
			puts("A!");	
			break;
		case 'b':
			puts("B!");
			break;
		default:
			puts("Does not start with an 'a' or 'b'");
	}
	return 0;
}
