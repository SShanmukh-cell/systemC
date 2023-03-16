#include <systemc.h>

SC_MODULE(half_adder){
	sc_in<sc_uint<1>> a, b;
        sc_out<sc_uint<1>> sum, carry;
	sc_in<bool> clr, clk;

	void h_adder(){
		if(clr){
			sum.write(0);
			carry.write(0);
		}
		else {
			sum.write(a.read() ^ b.read());
			carry.write(a.read() && b.read());
		}
	}

	SC_CTOR(half_adder){
		SC_METHOD(h_adder);
		sensitive << clk.pos();
		sensitive << clr.pos();
	}
};	
