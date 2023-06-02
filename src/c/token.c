/* Takes in input from the user and creats an array of string tokens. It does this twice, one with a custom funciton, the other with strtok */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN 10 //minimum allocs for token
#define MAX 1024 //max input for fgets
#define DELIMETER " ," //delim to test with

static void *w_alloc(void *ptr, const size_t ammount, const size_t size){
	//keeps attempting to allocate a zero'd array
	ptr = NULL;
	while(ptr == NULL){
		ptr = calloc(size, ammount);
	}
	return ptr;
}
static void *w_realloc(void *ptr, const size_t ammount, const size_t size){
	//keeps attempting to resize an array
	do {
		ptr = reallocarray(ptr, ammount, size);
	} while(ptr == NULL);
	return ptr;
}

char **tokenize(char *input, const char *delim, int *ammount){
	//tokenizes a string with a set delim, also sets the ammount, needs to be freed! Uses STRTOK, returns an array of strings
	char **output = NULL; //the array of pointers we are returning
	char *token = NULL; //string pointer for strtok
	char *save_ptr = NULL; //saves the place for strtok
	int token_count = 0; //how many tokens we find
	int output_size = MIN; //number of elements in output_size

	token = strtok_r(input, delim, &save_ptr); //initalize strtok
	output = w_alloc(output, MIN + 1, sizeof(char**)); //initalize the string array
	

	for(token_count = 0; token != NULL; token_count++){	
		if(token_count == output_size){
			output_size *= 2;
			//realloc if we are too small
			output = w_realloc(output, output_size, sizeof(char*));
		}

		output[token_count] = w_alloc(output[token_count], strlen(token)+1, sizeof(char));
		strncpy(output[token_count], token, strlen(token)); //copy the contents of the token to output
		token = strtok_r(NULL, delim, &save_ptr); //jump to the next token
	}
	*ammount = token_count;
	//resize the variable to save memory
	output = w_realloc(output, *ammount, sizeof(char*)); 
	return output;
}


char **token(const char input[], char delim, int *ammount){ 
	//tokenizes a string with a set delim, also sets the ammount, needs to be freed! Returns an array of strings
	int i = 0; //index of input
	int l = 0; //index of temp
	int token_count = 0; //how many tokens we found so far
	int output_size = MIN; //the size of output
	size_t input_size = strlen(input); //gets the how man chars are in input

	char **output = NULL; //the array of pointers we are returning
	char **temp = NULL; //a temp variable to check for null when reallocating output
	char *token = NULL; //the token we found

	output = w_alloc(output, MIN + 1, sizeof(char*)); //init output
			
	while(i < input_size){
	
		//search for delim or EOF
		for(i; input[i] != delim && input[i] != '\0'; i++){
			if(token == NULL) //putting it here prevents memory leaks
				token = w_alloc(token, input_size - i + 1, sizeof(char));
		
			token[l++] = input[i]; //adds the char from input to token
		}
		if(token != NULL && token[0] != '\0'){
			//allocate memory for it
			if(token_count + 1 > output_size){
				output_size *= 2; //TODO make it more memory concious
				//realloc if we are too small
				output = w_realloc(output, output_size, sizeof(char*));
			}
			token = w_realloc(token, strlen(token), sizeof(char)); //shrink the size of token
			output[token_count++] = token; //add the token to the array
			token = NULL; //reset the token to look for the next one
		}
		i++; //skips the delim in the loop
		l = 0; //resets the token index
	}
	*ammount = token_count; //alows us to return the ammount of tokens found
	//resize the variable to save memory
	output = w_realloc(output, *ammount, sizeof(char*)); //we should be able to go smaller without an error?
	return output;
}

int main(int argc, char *argv[]){
	char *input = NULL;
	input = w_alloc(input, MAX, sizeof(char));

	printf("Enter String [Max = %d]: ", MAX);
	fgets(input, MAX, stdin);
	input[strlen(input)-1] = '\0'; //removes the trailing '\n'

	int token_count = 0; //gets changed by the function to hold the ammount of tokens
	printf("Tokenizing: '%s'\n", input);
	char **words = NULL;

	//tokens using custom function
	words = token(input, DELIMETER[0], &token_count);
	
	int i = 0;
	for(i=0; i < token_count; i++){
		printf("[%d] '%s'\n", i, words[i]);
		free(words[i]);
	}
	free(words);
	puts(" ");


	//tokens using strtok
	words = tokenize(input, DELIMETER, &token_count);
	for(i=0; i < token_count; i++){
		printf("[%d] '%s'\n", i, words[i]);
		free(words[i]);
	}
	free(words);
	free(input);

	return 0;
}
