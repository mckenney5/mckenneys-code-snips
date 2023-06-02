/*
 * C++
 * Asks the user for their name and says hello
 * compile: g++ c-plus-plus.cpp -o c-plus-plus
 */

#include <iostream> // used to get input and output (cin cout)
#include <string> // used for string variables
using namespace std; // using the standard library so we dont have to use ::

int main(void){
	// display prompt
	cout << "Enter your name: ";

	// get user input
	string name = "\0";
	cin >> name;

	// say hello
	cout << "Hello " << name << "!\n";
	
	// exit without error
	return 0;
}
