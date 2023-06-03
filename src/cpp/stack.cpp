/* Handles stack manipulation */
#include <iostream> //cerr, cout
#include <vector> //vector 

using namespace std;

class Data_Stack {
	vector<long long> s; 
	//we use a vector so we can read the stack without modifiying it
	
	private: bool will_underflow(size_t ammount = 1){
		if(s.size() < ammount){
			cerr << "underflow.";
			error_flag = true;
			return true;
		}
		return false;
	}

	private: bool error_flag = false;

	public: bool check_error(bool flip_flag = true){
		//checks if an error happened, can clear error on read
		if(flip_flag == false)
			return error_flag;

		if(error_flag == true){
			error_flag = false;
			return true;
		}
		return false;
	}
	
	public: bool empty(){
		return s.empty();
	}
	
	public: size_t size(){
		return s.size();
	}
	
	public: long long top(){
		if(will_underflow(1)) return 0;
		return s.back();
	}

	public: long long bottom(){
		if(will_underflow(1)) return 0;
		return s.front();
	}

	public: void push(const long long val){
		s.push_back(val);
	}
	
	public: long long pop(size_t ammount = 1){
		//removes data from the stack and returns the item popped
		long long data = 0;
		for(size_t i = 0; i < ammount; i++){
			if(will_underflow(1)) return 0;
			data = s.back();
			s.pop_back();
		}
		return data;
	}
	
	public: void swap(){
		//swaps the two top most items
		long long a = pop(), b = pop();
		push(a);
		push(b);
	}
	
	public: void dup(size_t ammount = 1){
		//duplicates the top of the stack
		if(will_underflow(1)) return;
		for(size_t i = 0; i < ammount; i++){
			s.push_back(s.back());
		}
	}

	public: void over(){
		//duplicates the 2nd top most item
		if(will_underflow(2)) return;
		push(s[s.size()-2]);
	}

	public: void rot(){
		//Rotates third item to top
		//TODO optimize out the push and pop and use [] and index
		if(will_underflow(3)) return;
		long long a = pop();
		long long b = pop();
		long long c = pop();

		push(b);
		push(a);
		push(c);
	}

	public: void display(){
		cout << '<' << s.size() << "> ";
		for(size_t i = 0; i < s.size(); i++)
			cout << s[i] << " ";
	}
	
	public: void clear(){
		//Deletes the contents of the stack
		s.clear();
	}

	public: void debug(){
		//dumps all values
		cout << "Empty?\tSize\tTop\tBottom\tErr?" << endl;
		cout << empty() << '\t' << size() << '\t' << top();
		cout << '\t' << bottom() << '\t' << check_error(false) << endl << endl;
		display();
		cout << endl;
	}
} ds;
/*
int main(){
	//testing script
	Data_Stack ds;
	for(long long i = 0; i < 10; i++)
		ds.push(i);
	ds.over();
	ds.swap();
	ds.dup();
	ds.debug();
	ds.rot();
	cout << "rot:" << endl;
	ds.debug();
	cout << "clearing stack..." << endl;
	ds.clear();
	ds.display();
	ds.pop(100); //should underflow
	ds.debug();
	cout << endl;
	return 0;
}
*/
