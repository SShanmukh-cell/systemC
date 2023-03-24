#include <systemc.h>
#include "const.h"

// Half Adder module
SC_MODULE(HalfAdder) {
    sc_in<sc_bv<1>> a, b;
    sc_out<sc_bv<1>> sum, carry;
    sc_in<bool> clk, reset;

    void half_adder_process() {
	    if(reset){
		    sum.write(0);
		    carry.write(0);
	    }
	    else {
		    sum.write(a.read() ^ b.read());        // XOR gate for sum
                    carry.write(a.read() & b.read());     // AND gate for carry
	    }
    }

    SC_CTOR(HalfAdder) {
        SC_METHOD(half_adder_process);
        sensitive << a << b;
	sensitive << clk.pos();
    }
};



