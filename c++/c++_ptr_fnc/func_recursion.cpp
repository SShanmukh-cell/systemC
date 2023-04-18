#include <iostream>
#include <string>
using namespace std;

int factorial(int a);


int main(){   //  here the function_n must be declared before main otherwise will throw an error. or-else i can declare the function before and give definition after the main
	int z = factorial(5);
	cout << " z = " << z << endl;
	return 0;
}

int factorial(int a){
	if(a>0){
		return a * factorial(a-1);
	}
	else {
		return 1;
	}
}
