#include <iostream>
#include <string>
using namespace std;

int func_add(int a, int b);
double func_add(double a, double b); //  we can use same function name but with different data type, which is called function overloading
double func_add(double a, int b);    //  64-bit type that can represent numbers with up to 15 decimal digits of precision
float func_add(float a, float b);    //  32-bit type that can represent numbers with up to 7 decimal digits of precision

int main(){   //  here the function_n must be declared before main otherwise will throw an error. or-else i can declare the function before and give definition after the main
	int x = func_add(5, 7);
	double y = func_add(5.5, 7.0);
	double z = func_add(5.5, 7);
	float f = func_add(5.5, 7);
	cout << "int x = " << x << " double y = " << y << " double z = " << z << " f = " << f << endl;
	return 0;
}

int func_add(int a, int b){
	return a * b;
}

double func_add(double a, double b){
	return a * b;
}

double func_add(double a, int b){
	return a * b;
}

float func_add(float a, float b){
	return a * b;
}
