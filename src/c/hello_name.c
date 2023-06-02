/*
 * The C programming language
 * Takes the users name and says hello
 * to compile: gcc c.c -o c
*/

#include <stdio.h> // include the standard library for 'printf' and 'fgets'
int main(void){
	// display prompt
	printf("Enter your name: ");

	// get the name
	char name[1024] = {'\0'};
	fgets(name, 1024, stdin);

	// remove the new line char from the input
	int i = 0;
	for(i=0; name[i] != '\n' && i != 1024-1; i++) NULL; // look for the newline char
	name[i] = '\0'; // remove the new line char

	// display the name
	printf("Hello %s!\n", name);

	// exit normally
	return 0;
}

