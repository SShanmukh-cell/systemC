#include <iostream>
#include <string>
using namespace std;

/*void function_n(){
	cout << "new function created" << endl;
}

int main(){   //  here the function_n must be declared before main otherwise will throw an error.
	function_n();
	return 0;
}*/



void function_n();

int main(){   //  here the function_n must be declared before main otherwise will throw an error. or-else i can declare the function before and give definition after the main
	function_n();
	return 0;
}

void function_n(){
	cout << "new function created" << endl;
}
