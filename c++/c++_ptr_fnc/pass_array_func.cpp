#include <iostream>
#include <string>
using namespace std;

void pass_array_func(int num[5]);   

int main(){   //  here the function_n must be declared before main otherwise will throw an error. or-else i can declare the function before and give definition after the main
	int num[5] = {5, 6, 1, 18, 100};
	pass_array_func(num);
	return 0;
}

void pass_array_func(int num[5]){
	for(int i = 0; i<5 ; i++){
		cout << "num[" << i << "] = " << num[i] <<  endl;
	}
}
