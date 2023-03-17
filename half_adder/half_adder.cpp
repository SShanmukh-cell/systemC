#include <systemc.h>
#include "const.h"


SC_MODULE(half_adder){
	sc_in<sc_bv<data_width>> a, b;
        sc_out<sc_bv<data_width>> sum;
        sc_out<sc_logic> carry;
	sc_in<bool> clr, clk;

	void h_adder(){
		sc_bv<data_width> a0 = a.read();   /// 
		sc_bv<data_width> b0 = b.read();
		sc_bv<data_width> s0, c0;
		sc_logic c;
		        
                int i;


		if(clr){
			sum.write(0);
			carry.write(SC_LOGIC_0);  /// if the data type is sc_logic that writing false or 0 will throw an error, so we give SC_LOGIC_0/SC_LOGIC_1/SC_LOGIC_X/SC_LOGIC_Z
		}
		else {
			for( i = 0; i < data_width; i++){
				if(i == 0){
					s0[i] = a0[i] ^ b0[i];    ///////// i === 0 i.e only for the first bit since we dont have carry here as input 
		                        c0[i] = a0[i] & b0[i];
				}
			        else{
				        s0[i] = a0[i] ^ b0[i] ^ c0[i-1];
		                        c0[i] = (a0[i] & b0[i]) | (a0[i] & c0[i-1]) | (c0[i-1] & b0[i]);
				        c = c0[i];
			        }
			}
	


			sum.write(s0);
			carry.write(c);
		}
	}

	SC_CTOR(half_adder){
		SC_METHOD(h_adder);
		sensitive << clk.pos();
		sensitive << clr.pos();
	}
};	
