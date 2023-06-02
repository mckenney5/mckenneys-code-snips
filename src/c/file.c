/* reads in a file and display it to the screen using streams */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1024 //largest file to read

int main(int argc, char *argv[]){
	if(argc != 2){
		fprintf(stderr, "Usage: '%s <text-file-name>'\n", argv[0]);
		return EXIT_FAILURE;
	}

	FILE *fp;
	char page[MAX_SIZE] = {0};
	fp = fopen(argv[1], "r");
	if(fp == NULL){ perror("fopen"); return EXIT_FAILURE; }
	size_t i;
	for(i=0; i < MAX_SIZE; i++){
		page[i] = fgetc(fp);
		if(page[i] == EOF) break;
	}
	page[i] = '\0';
	fclose(fp);
	printf("Size: '%ld'\nText: '%s'\n", strlen(page), page);

	return EXIT_SUCCESS;
}

