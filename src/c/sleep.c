/* A delay example with nano sleep */
#include <time.h>    //nanosleep
#include <stdlib.h>  //atol
#include <stdio.h> //fprintf, EXITs
#include <unistd.h>

void delay_micro(unsigned int delay){
	usleep(delay);
}

void delay_nano(unsigned long delay1, unsigned long delay2){
	struct timespec tim, tim2;
	tim.tv_sec = delay1;
	tim.tv_nsec = delay2;
	nanosleep(&tim, &tim2);
}

int main(int argc, char *argv[]){
	if(argc == 2)
		delay_micro((unsigned) atoi(argv[1]));
	else if(argc == 3)
		delay_nano((unsigned) atol(argv[1]), (unsigned) atol(argv[2]));
	else {
		fprintf(stderr, "Usage: '%s <time-in-micro-sec>' or '%s <time-in-seconds> <time-in-nano-sec>'\n", argv[0], argv[0]);
		return EXIT_FAILURE;
	}	
	return EXIT_SUCCESS;
}

