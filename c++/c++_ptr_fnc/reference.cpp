#include <iostream>
#include <string>
using namespace std;

string food = "KFC";
string &meal = food;   //  here meal is the reference to food  


int main(){
	cout << "food is " << food << endl;
	cout << "meal which is reference to food is " << meal << endl;
	cout << "memory address of food is " << &food << endl;            ///  to print the address where the food and meal is stored, we can print by using '&' before the varible name.
	cout << "memory address of meal is " << &meal << endl;

	food = "Pasta";                          // if I change food, meal automatically get reflected and vice-versa.
	cout << "food is " << food << endl;
	cout << "meal which is reference to food is " << meal << endl;
	cout << "memory address of food is " << &food << endl;
	cout << "memory address of meal is " << &meal << endl;

	meal = "Chicken";                        // if I change meal, food automatically get reflected and vice-versa.  
	cout << "food is " << food << endl;
	cout << "meal which is reference to food is " << meal << endl;
	cout << "memory address of food is " << &food << endl;
	cout << "memory address of meal is " << &meal << endl;

}
