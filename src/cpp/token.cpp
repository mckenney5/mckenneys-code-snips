//Yet another scripting language
#include <iostream> //cout
#include <cassert> //assert
#include <climits> //LLONG_MAX/MIN
#include <fstream> //ifstream
#include <vector> //vector
#include <string> //string
#include <map> //map
#include <cctype> //isdigit

using namespace std;

// Global Vars
const string PROGRAM_NAME = "YASL";
const char END = ';'; //loops until this char is found
size_t exe_ptr = 0; //where we are in the tokens


class SourceFile {
	//loads a source file and tokenizes it
	bool initalized = false;
	vector<string> tokens;
	string actual_file_name;
	
	public: bool open(const string file_name){
		ifstream text_file;
		text_file.open(file_name);
		if(!text_file){
			cerr << "Cannot open '" << file_name << "'" << endl;
			return false;
		}
		initalized = true;
		actual_file_name = file_name;
		
		string token;
		string temp;
		
		while(getline(text_file, token, ' ')){
			//cout << "'" << token << "'\n";
			if(token != "" && token != "\n"){
				for(size_t i = 0; i < token.length(); i++){
					if(token.at(i) != '\t'){ //TODO replace with a filter function
						if(token.at(i) == '\n'){ //if a newline is found, treat it as a token
							tokens.push_back(temp);
							temp = "";
						} else
							temp += token.at(i);
					}
				}
				tokens.push_back(temp); //add temp to the end of the vectors of strings
				temp = "";
			}
		}
		text_file.close();
		tokens.shrink_to_fit(); //resizes the vector to minimize data needed
		return true;
	}
	
	public: string token(size_t index = 0){
		if(!initalized){
			cerr << "Cannot access token since no source file was loaded." << endl;
			return "";
		} else if(index >= tokens.size()){
			cerr << "Cannot access token since the index " << index << " >= " << tokens.size() << " (ammount of tokens)" << endl;
			return "";
		} else
			return tokens[index];
	}
	public: string peek(size_t offset){
		//looks ahead or behind, without incrementing the exe_ptr
		return token(exe_ptr + offset);
	}
	public: bool change_token(const string new_token, const size_t index){
		if(index >= tokens.size()){
			cerr << "Cannot access token since the index " << index << " >= " << tokens.size() << " (ammount of tokens)" << endl;
			return false;
		} else {
			tokens[index] = new_token;
			return true;
		}
	}
	
	public: string get_file_name(){
		return actual_file_name;
	}
};

class Variables {
	//holds maps of variables
	private: map<string, long long> numbers = {
    { "_MAX_NUMBER", LLONG_MAX },
    { "_MIN_NUMBER", LLONG_MIN },
	};
	
	private: map<string, string> strings = {
    { "_PROGRAM_NAME", PROGRAM_NAME }, //Example
	};
	
	public: void add(const string name, const long long value){
		if (!isInNumber(name) && !isInString(name)){
			numbers.insert(pair<string, long long>(name, value));
		} else if(isInString(name)){
			strings.erase(name); //convert variable from string to number by removing it from strings and adding it to numbers
			numbers.insert(pair<string, long long>(name, value));
		} else {
			numbers[name] = value; //update the value if it is only in the numbers
		}
	}
	
	public: void add(const string name, const string value){
		if (!isInString(name) && !isInNumber(name)){
			strings.insert(pair<string, string>(name, value));
		} else if(isInNumber(name)){
			numbers.erase(name); //convert variable from number to string
			strings.insert(pair<string, string>(name, value));
		} else {
			strings[name] = value; //update the value if it is only in the numbers
		}
	}
	
	public: bool search(const string name){
		return isInNumber(name) | isInString(name);
	}
	public: bool isInString(const string name){ //TODO make private?
		return strings.find(name) != strings.end();
	}
	public: bool isInNumber(const string name){
		return numbers.find(name) != numbers.end();
	}
	public: void display(){
		cout << "---Numbers---" << endl;
		for (auto itr = numbers.begin(); itr != numbers.end(); itr++) //creates an itterator and that goes through the map
			cout << itr->first << " = " << itr->second << endl;
		cout << endl << "---Strings---" << endl;
		for (auto itr = strings.begin(); itr != strings.end(); itr++)
			cout << itr->first << " = " << "'" << itr->second << "'" << endl;
		cout << endl;
	}
	public: string string_value(const string name){
		assert(strings.find(name) != strings.end()); //makes sure the string exists
		return strings[name];
	}
	public: long long number_value(const string name){
		assert(numbers.find(name) != numbers.end()); //makes sure the number exists
		return numbers[name];
	}
};

// Global Objects
SourceFile sourcefile;
Variables variables;

bool isop(string op){
	if(op == "+" || op == "-" || op == "*" || op == "/" || op == "%")
		return true;
	else
		return false;
}

void handle_op(string num1, string op, string num2){
	//assuming the exe_ptr is pointing to the op
	long long lnum1 = stoll(num1);
	long long lnum2 = stoll(num2);

	if(op == "+"){
		cout << lnum1 + lnum2 << endl;
	}
}

void handle_number(){
	if(isop(sourcefile.token(++exe_ptr))){ //if the next token is an operator - TODO FIXME check logic
		if(isdigit(sourcefile.token(exe_ptr + 1)[0])) //and the next token after that is a number
			handle_op(sourcefile.token(exe_ptr), sourcefile.token(exe_ptr-1), sourcefile.token(++exe_ptr));
		else { //if it is a variable
			//set token to value of variable (gets the number value, makes it a string, and overwrites the token
			sourcefile.change_token(to_string(variables.number_value(sourcefile.token(exe_ptr + 1))), exe_ptr + 1);
			exe_ptr--; //since we replaced the var, go back and try again
			handle_number();
		}
	}
}


void handle_command(){
	//look up command in map, if found, run function pointer
}

void handle_var(const string key, const string value){
	if(isdigit(value[0]))
		variables.add(key, stoll(value));
	else
		variables.add(key, value);
}

int interpet(){
	if(!sourcefile.open("test.txt")){
		perror("Error opening file. ");
		return EXIT_FAILURE; //TODO add an error handling object
	}

	string tok = "";
	tok = sourcefile.token(exe_ptr);
	
	for(exe_ptr = 0; tok != ""; tok = sourcefile.token(++exe_ptr)){
		cout << tok << endl;
		if(isdigit(tok[0]))
			handle_number();
		else if(isop(sourcefile.token(exe_ptr + 1)))
			handle_op(sourcefile.token(exe_ptr), sourcefile.token(++exe_ptr), sourcefile.token(++exe_ptr));
		else if(sourcefile.token(exe_ptr + 1) == "=") //FIXME this does not get called, it runs isop instead
			handle_var(sourcefile.token(exe_ptr++), sourcefile.token(++exe_ptr));
		else
			handle_command();
	}
	//loop through each token and assign them to the right place
	//if token is variable
	//	- check what kind of var
	//	- add it to the map in variables
	//else if token is an operator
	//	- check if the operator refrences a variable
	// 		- if so, replace variable with value
	// else
	// - run the command via shell (temp)
	return 0;
}

void test(){
	//tests functions of the program
	sourcefile.open("test.txt");
	cout << "The first token is: '" << sourcefile.token() << "'" << endl;
	cout << "The second token is: '" << sourcefile.token(1) << "'" << endl;
	//cout << "The thirty-seventh token is: '" << sourcefile.token(13) << "'" << endl; //should crash with error
	
	variables.add("funny", 42069); //add a number variable
	variables.add("my_name", "Adam"); //add a string
	cout << "Variable Maps:" << endl;
	variables.display();
	
	cout << "Checking for var cow..." << boolalpha << variables.search("cow") << endl; //prints false
	cout << "Checking for var bar..." << boolalpha << variables.search("bar") << endl; //prints true
	cout << "Checking for var dog..." << boolalpha << variables.search("dog") << endl; //prints true
	cout << "Converting bar to a string." << endl;
	variables.add("bar", "foo");
	cout << "Converting my_name to a number" << endl;
	variables.add("my_name", 27);
	variables.display();
	cout << "Checking value of my_name: " << variables.number_value("my_name") << endl;
	//cout << "Checking value of my_name: " << variables.string_value("my_name") << endl; //should fail with an error
	
}

int main(){
	//test();
	//interpet();
	
	variables.display();
	return 0;
}
