//creates a safe llong object that wont overflow
#include <climits> //LLONG_MAX/MIN
#include <stdio.h> //fprintf
#include <cstdlib> //abs
#include <cassert> //assert
#include <string>

using namespace std;

class snum {
	long long number = 0;
	bool initalized = false;
	private: long long change_by(const int x){ //TODO Add generics
		//assert(initalized);
		short change = 1;
		if(x == 0)
			return number;
		else if(x < 0)
			change = -1;

		snum i; //use a safe number for the internal for loop to stop overflows
		for(i.set(0); i.value() < abs(x); i.inc()){
			if(number == LLONG_MAX && change == 1){
				fprintf(stderr, "snum cannot increment due to overflow!\n");
				return number;
			} else if(number == LLONG_MIN && change == -1){
				fprintf(stderr, "snum cannot decrement due to underflow\n");
				return number;
			} else {
				number += change;
			}
		}
		return number;
	}
	public: long long value(){
		return number;
	}
	public: long long inc(){
		//instead of having this call change_by, it does its own thing to prevent a stack overflow due to recursion in change_by
		if(number == LLONG_MAX){
			fprintf(stderr, "snum cannot increment due to overflow!\n");
			return number;
		} else {
			return ++number;
		}
	}
	public: long long inc(const int x){
		return change_by(x);
	}

	public: long long dec(){
		return change_by(-1);
	}
	public: long long dec(const int x){
		return change_by(x * -1);
	}

	public: long long set(const long long new_value){
		if(!initalized) initalized = true;
		number = new_value;
		return number;
	}
};

int main(){
	snum i;
	
	//i.inc(); //should error

	i.set(LLONG_MAX - 20);

	long long end = LLONG_MAX - 1;

	for(; i.value() <= end; i.inc(5))
		printf("%lld ", i.value());
	putchar('\n');
	i.set(LLONG_MAX);
	i.inc();
	i.set(LLONG_MIN);
	i.dec();
	i.set(LLONG_MAX);
	printf("%lld %lld %lld %lld %lld\n", i.value(), i.inc(5), i.dec(5), i.inc(-5), i.dec(-5));
	return 0;
}

