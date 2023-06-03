/* Handles holding words and built in words */

#include <iostream>
#include <stdio.h>
#include <stdlib.h> //system
#include <functional> //function
#include <map>

#include "stack.cpp" //allows words to manipulate the stack
#include "easy_token.h" //tokenizes words

using namespace std;

//Built in words

void test2(){
	cout << "Tada!" << endl;
}

void pop(){
	cout << ds.pop();
}

void page(){
	//HACK TODO use fancy escape codes
	system("clear");
}

void emit(){
	putchar((char)ds.pop());
}

long long handle_operator(const string op){
	switch(op[0]){
		case '+': return (ds.pop() + ds.pop());
		case '-': return (ds.pop() - ds.pop());
		case '/': return (ds.pop() / ds.pop());
		case '*': return (ds.pop() * ds.pop());
		case '<': return (long long)(ds.pop() < ds.pop());
		case '>': return (long long)(ds.pop() > ds.pop());
		case '=': return (long long)(ds.pop() == ds.pop());
		case '&': return (long long)(ds.pop() & ds.pop());
		case '|': return (long long)(ds.pop() | ds.pop());
		case '^': return (long long)(ds.pop() ^ ds.pop());
		case '%': return (ds.pop() % ds.pop());
	}
	if(op == "MOD")
		return (ds.pop() % ds.pop());
	else
		cerr << "Not implemented *yet*.";
	return 0;
}

//--

bool is_digit(const string input){
    char *p = 0;
    strtoll(input.c_str(), &p, 10);
    return *p == 0;
}

bool is_operator(const string input){
        if(input[1] == '\0'){
		switch(input[0]){
		case '+':
		case '-':
		case '/':
		case '*':
		case '<':
		case '>':
		case '=':
		case '&':
		case '|':
		case '^':
		case '%': return true; //TODO check if this is standard
		default:
			return false;
		}
        } else {
		if(input == "MOD" || input == "/MOD")
			return true;
		else
			return false;
	}
}

class Words {
	const vector<string> ignore_list = {" ", "\n", "\0"};
	
	bool in_comment = false;

	map<string, string> UNcompiled_words = {
	{ "PAGE", "TEST" },
	{ "TEST", "30 EMIT" },
	{ "MOD", "%" },
	{ "AND", "&" },
	{ "OR", "|" },
	{ "XOR", "^" },
	};
	
	map<string, function<void()>> compiled_words = {
	{ "TEST2", &test2 },
	{ "PAGE", &page },
	{ "EMIT", &emit },
	{ ".", &pop },
	};

	string handle_comment(const string name){
		//ignores words until we find the end of the comment
		//then returns words we can actually use

		string cleaned_word = "";
		
		//ignore input until we see a ')'
		size_t found = name.find(")");
		if(found != name.npos){ //if found
			in_comment = false; //stop ignoring
			for(size_t i = found+1; i < name.size(); i++)
				cleaned_word.append(1u, name[i]);
		}
		return cleaned_word; //run the word without the '... )'
	}


	public: bool run(const string name){
		
		//checks if the input is in the ignore list
		for(size_t i = 0; i < ignore_list.size(); i++)
			if(name == ignore_list[i]) return true;
		
		if(in_comment) return run(handle_comment(name));

		if(UNcompiled_words.find(name) != UNcompiled_words.end()){
			vector<string> commands = tokenize(UNcompiled_words[name]);
			for(size_t i = 0; i < commands.size(); i++)
				run(commands[i]);
			
		} else if(compiled_words.find(name) != compiled_words.end())
			compiled_words[name]();
		else if(is_digit(name))
			ds.push(stoll(name));
		else if(is_operator(name))
			ds.push(handle_operator(name));
		else if(name == "(") 
			in_comment = true;
		else {
			cerr << "Undefined word '" << name << "'.";
			ds.clear(); //destroy the stack, as is the forth way
			return false;
		}
		return true;
	}
} w;

/*
int main(){
	//ds.push(10);
	//ds.push(37);
	w.run("10");
	w.run("41");
	ds.debug();
	w.run("EMIT");
	w.run("EMIT");
	w.run("1");
	w.run("2");
	w.run("+");
	w.run(".");
	w.run("(");
	w.run("4");
	w.run("5");
	w.run("+)2");
	ds.debug();
	return 0;
}*/
