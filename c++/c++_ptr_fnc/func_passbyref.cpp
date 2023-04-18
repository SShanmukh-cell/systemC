#include <iostream>
#include <string>
using namespace std;

void swap_num(int &x, int &y);   

int main(){   //  here the function_n must be declared before main otherwise will throw an error. or-else i can declare the function before and give definition after the main
	int a, b;
	a = 10;
	b = 20;
	cout << "Before swapping" << endl;
	cout << "a = " << a << " b = " << b << endl;

	swap_num(a, b);
	cout << "After swapping" << endl;
	cout << "a = " << a << " b = " << b << endl;
	return 0;
}

void swap_num(int &x, int &y){
	int z;
	cout << "z = " << z << ", x = " << x << ", y = " << y << endl;
	z = x;
	x = y;
	y = z;	
	cout << "z = " << z << ", x = " << x << ", y = " << y << endl;
}
