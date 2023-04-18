#include <iostream>
#include <string>
using namespace std;

int func_w_param(int a, int b);   

int main(){   //  here the function_n must be declared before main otherwise will throw an error. or-else i can declare the function before and give definition after the main
	int z;
	z = func_w_param(5, 9);
	cout << "z = " << z << endl;
	return 0;
}

int func_w_param(int x, int y){
	cout << "x*y = " << x*y << endl;
	return x * y;
}
