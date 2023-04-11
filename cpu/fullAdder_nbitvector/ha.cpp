#include <systemc.h>
#include "const.h"

// Half Adder module
SC_MODULE(HalfAdder) {
    sc_in<sc_biguint<1>> a, b;
    sc_out<sc_biguint<1>> sum, carry;
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

    SC_CTOR(HalfAdder):
	    a("ha_a"),
	    b("ha_b"),
	    sum("ha_sum"),
	    carry("ha_carry"),
	    clk("ha_clk"),
	    reset("ha_reset")
	{
        SC_METHOD(half_adder_process);
        sensitive << a << b;
	sensitive << clk.pos();
	sensitive << reset.pos();
    }
};



