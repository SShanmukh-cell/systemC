#include <systemc.h>
#include "const.h"


SC_MODULE(HalfSubtractor) {
    sc_in<sc_bv<1>> a, b;
    sc_out<sc_bv<1>> difference, borrow;
    sc_in<bool> clk, reset;

    void half_subtractor_process() {
	    if(reset){
		    difference.write(0);
		    borrow.write(0);
	    }
	    else {
		    difference.write(a.read() ^ b.read());        // XOR gate for difference
                    borrow.write((~a.read()) & b.read());     // AND gate for borrow
	    }
    }

    SC_CTOR(HalfSubtractor) {
        SC_METHOD(half_subtractor_process);
        sensitive << a << b;
	sensitive << clk.pos();
	sensitive << reset.pos();
    }
};



