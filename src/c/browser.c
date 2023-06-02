/* Does an HTTP GET request */
/* ./a.out <website> <optional_file> */
/* example: ./a.out index.html example.com */
#include <stdio.h>
#include <string.h>

#define ACCEPT "text/html"
#define USER_AGENT "netcat/1.10"
#define ACC_LANG "en"
#define CONNECTION "close"

int main(int argc, char* argv[]){
	if(argc == 3 || argc == 2){
		if(argv[2] == NULL) printf("GET / "); //stops printf for putting '(null)'
		else printf("GET /%s ", argv[2]);
		printf("HTTP/1.0\r\nUser-Agent: %s\r\nAccept: %s\r\nAccept-Language: %s\r\nConnection: %s\r\nHost: %s\r\n\r\n", 
			USER_AGENT, ACCEPT, ACC_LANG, CONNECTION, argv[1]);
	} else {
		fprintf(stderr, "Syntax error. Usage:\n\t%s <website> <optional_file>"
			"\n\tExample: %s example.com index.html | nc example.com 80\n", argv[0], argv[0]);
		return -1;
	}
	return 0;
}

