#include <iostream>
#include <vector>

#include "words.cpp"
#include "easy_token.h"

//extern "C" {
	#include "lib/linenoise.h"
//}

const char* PROMPT = "f> ";

using namespace std;

string get_input(){
	string string_inpt = "";
	char *inpt = linenoise(PROMPT);

	//conver cstring to string
	if(inpt != NULL){
		for(size_t i = 0; inpt[i] != '\0'; i++)
			string_inpt.append(1u, inpt[i]);
	}
	string_inpt.append(1u, '\0');

	free(inpt);
	return string_inpt;
}

void clear_vec(vector<string> *v){
	for(size_t i = 0; i < v->size(); i++)
		v->at(i) = "\0";
	v->clear();
}

int main(int argc, char *argv[]){
	//string inpt = "";
	vector<string> new_words;
	bool error_flag = false;

	while(true){
		new_words = tokenize(get_input());

		//cerr << "new_words='" << words[0] << "'\n";

		for(size_t i = 0; i < new_words.size(); i++){
			if(new_words[i] == "bye" || new_words[i] == "BYE") return 0;

			if(w.run(new_words[i]) == false){
				cout << endl << endl;
				error_flag = true;
				break;
			}
		}

		if(!error_flag){
			cout << "  ok." << endl;
		}
		
		error_flag = false;
		clear_vec(&new_words);
	}
	return 0;
}

