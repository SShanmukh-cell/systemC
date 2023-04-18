#include <iostream>
#include <string>
using namespace std;

void func_w_param(string name = "Shanmukh", int age = 22);  //  setting default value to 

int main(){   //  here the function_n must be declared before main otherwise will throw an error. or-else i can declare the function before and give definition after the main
	func_w_param("Ajay", 23);
	return 0;
}

void func_w_param(string name, int age){
	cout << "Name given as input is " << name << " Age is " << age << endl;
}


