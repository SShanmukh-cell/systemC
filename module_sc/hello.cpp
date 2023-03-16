#include <systemc.h>

SC_MODULE(hello_world){
	SC_CTOR(hello_world){
	}
	void func(){
		cout << "Hello World!" << endl;
	}
};

int sc_main(int agrc, char* argv[]){
	hello_world hello("");  // the string we are passing here is constructor argument that can be any string and its mandatory to pass any string 
	hello.func();
	return 0;
}
