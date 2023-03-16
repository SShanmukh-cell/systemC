#include <systemc.h>
//#include <string>    ////   intially thrown an error saying string not found, so we have to add 'using std::string;' in systemc.h file at line 210

int sc_main(int argc, char* argv[]){
	string name;
	getline(cin, name);
	cout << "Good Morning! " << name << endl;
	//cout << "size of string is: " << name.size() << endl;
	if(!name.size()) cerr << "Please Enter valid name!" << endl;   //  unlike cout, cerr will print errage message in the console output


	//  variables can be initialized in following three ways
	int a = 10;
	float b(5.56);    
	float c{2.9};
	cout << "sum of a, b, c is: " << a+b+c << endl;
	return 0;
}
	

