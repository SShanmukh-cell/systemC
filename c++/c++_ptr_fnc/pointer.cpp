#include <iostream>
#include <string>
using namespace std;

string food = "KFC";
string &meal = food;   // here meal is the reference to food 
string* ptrf = &food;
string *ptrm = &meal;  // pointer data type should be same as variable data type


int main(){
	cout << "food is " << food << endl;
	cout << "meal which is reference to food is " << meal << endl;
	cout << "memory address of food is " << &food << endl;            ///  to print the address where the food and meal is stored, we can print by using '&' before the varible name.
	cout << "memory address of meal is " << &meal << endl;
	cout << "pointer of food is " << ptrf << endl;
	cout << "pointer of meal is " << ptrm << endl;

	food = "Pasta";                          // if I change food, meal automatically get reflected and vice-versa.
	cout << "food is " << food << endl;
	cout << "meal which is reference to food is " << meal << endl;
	cout << "memory address of food is " << &food << endl;
	cout << "memory address of meal is " << &meal << endl;
	cout << "pointer of food is " << ptrf << endl;
	cout << "pointer of meal is " << ptrm << endl;

	meal = "Chicken";                        // if I change meal, food automatically get reflected and vice-versa.  
	cout << "food is " << food << endl;
	cout << "meal which is reference to food is " << meal << endl;
	cout << "memory address of food is " << &food << endl;
	cout << "memory address of meal is " << &meal << endl;
	cout << "pointer of food is " << ptrf << endl;          //  reference: output is memory address of food with the pointer
	cout << "pointer of meal is " << ptrm << endl;

	cout << "pointer of food has " << *ptrf << endl;        // dereference: output is value of food with the pointer
	cout << "pointer of meal has " << *ptrm << endl;

	*ptrm = "Eggs";                                         //  changed the pointer value of food, changes the value of all 
	cout << "food is " << food << endl;
	cout << "meal which is reference to food is " << meal << endl;
	cout << "memory address of food is " << &food << endl;
	cout << "memory address of meal is " << &meal << endl;
	cout << "pointer of food is " << ptrf << endl;          
	cout << "pointer of meal is " << ptrm << endl;
	cout << "pointer of food has " << *ptrf << endl;        
	cout << "pointer of meal has " << *ptrm << endl;

}
