#include <systemc.h>
#include "const.h"


SC_MODULE(full_adder){
	sc_in<sc_bv<bit_length>> a, b, ci;
	sc_in<bool> clr, clk;
	sc_out<sc_bv<bit_length>> sum;
	sc_out<sc_logic> carry;

	void f_adder(){
		sc_bv<bit_length> a0 = a.read();
       	        sc_bv<bit_length> b0 = b.read();
	        sc_bv<bit_length> c0in = ci.read();
	        sc_bv<bit_length> s0, cout;
	        sc_logic c;

	        int i;

		if(clr){
			sum.write(0);
			carry.write(SC_LOGIC_0);  /// if the data type is sc_logic that writing false or 0 will throw an error, so we give SC_LOGIC_0/SC_LOGIC_1/SC_LOGIC_X/SC_LOGIC_Z
		}
		else {
			for(i = 0; i < bit_length ; i++){
				if(i == 0){           ///   here we dont assign i=0, because i=0 is false condition and will never enter into if condition
					s0[i] = a0[i] ^ b0[i] ^ c0in[i];
	                                cout[i] = (a0[i] & b0[i]) | (a0[i] & c0in[i]) | (b0[i] & c0in[i]);
				}
			        else{
				        s0[i] = a0[i] ^ b0[i] ^ cout[i-1];
	                                cout[i] = (a0[i] & b0[i]) | (a0[i] & cout[i-1]) | (b0[i] & cout[i-1]);				        /
			        }
	                        c = cout[i];            ///// here since c is logic and cout is bit vectir, we have to extract a perticular bit from cout and assign it to c. 
			}

	                sum.write(s0);
	                carry.write(c);
		}
	}

	SC_CTOR(full_adder){
		SC_METHOD(f_adder);
		sensitive << clk.pos();
		sensitive << clk.pos();
	}
};
