/* basic use of ncurses, requires -lncurses to compile and libncurses5-dev */
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h> //needs to be compiled with -lncurses

int main(){
	initscr(); //creates the screen

	raw(); //ignore breaks (Ctrl-C)

	start_color(); //initalize colors

	printw("Hello, World\nColors: "); //print out a string like printf

	size_t i = 0;
	for(i=0; i < 8; i++){
		init_pair(i, 0, i); //create a color combo
		attron(COLOR_PAIR(i)); //turn on the color combo
		printw("%d ", i);
		attroff(COLOR_PAIR(i)); //turn off the color combo
	}

	getch(); //wait for a key to be pressed

	endwin(); //destroy the screen

	return EXIT_SUCCESS;
}
