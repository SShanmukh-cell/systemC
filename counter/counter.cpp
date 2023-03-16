#include <systemc.h>

SC_MODULE(counter){
	sc_in<bool> clk;
	sc_in<bool> clr;
	sc_out<sc_uint<4>> count;

	int incr;
	void func_counter();

	SC_CTOR(counter){
		incr = 0;
		
		SC_METHOD(func_counter);
		  sensitive << clk.pos();
		  sensitive << clr.pos();
		
	}
};





