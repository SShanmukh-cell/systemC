#include <systemc.h>
#include "const.h"


SC_MODULE(half_adder){
	sc_in<bool> a, b;
        sc_out<bool> sum;
        sc_out<bool> carry;
	sc_in<bool> clr, clk;

	void h_adder(){		        
                int i;
		if(clr){
			sum.write(0);
			carry.write(0);  /// if the data type is sc_logic that writing false or 0 will throw an error, so we give SC_LOGIC_0/SC_LOGIC_1/SC_LOGIC_X/SC_LOGIC_Z
		}
		else {
			sum.write(a xor b);
			carry.write(a and b);
		}
	}

	SC_CTOR(half_adder){
		SC_METHOD(h_adder);
		sensitive << clk.pos();
		sensitive << clr.pos();
	}
};	
