#include <systemc.h>
#include "const.h"


SC_MODULE(left_shift_N) {
	sc_in<sc_biguint<N>> inp;
	sc_in<sc_biguint<N>> shift_by;
	sc_out<sc_biguint<N+N>> out;
	sc_in<bool> clk, rst;
	sc_in<sc_biguint<N>> valid;

	void left_shift_func(){
		sc_bv<N+N> temp0;
		sc_bv<N> shift0, valid_high;
		int i, j;

		shift0 = shift_by.read();
		valid_high = valid.read();    /// here i am using valid for two purpose, 1. for left shift so that code can be more flexible and reusable to get the output for only perticular instance 
					      //                                         2. for multiplier(in this case) so that i can get the output only when the multiplier bit is high, 0 otherwise
		if(rst){
			out.write(0);
		}
		else {
			if(valid_high != 0b0){     //  here i am using valid as active high. NOTE: remember to code the multiplier with active high valid 
				if(shift0 == 0b0){
					out.write(inp.read());
				}
				else {
					temp0 = inp.read();
			
					sc_uint<N> s;
					s = shift0;
					for(j = N-1; j >= 0; j--){
						temp0[j+s] = temp0[j];     //  directly taking all the input bits and shifting it by s/shift0/shift_by bits
						if(j==0) {
							for(i = s-1; i >= 0; i--){     // this for loop is for the bits which are shifted and need to be assigned with 0 (from lsb bits)
								temp0[i] = 0;
							}
						}
					}			
					out.write(temp0);
				}
			}
			else{                                    ////  if not valid give the output 0
				out.write(0);
			}

		}			
	}

	SC_CTOR(left_shift_N):
		inp("ls_inp"),
		shift_by("ls_shift_by"),
		out("ls_out"),
		valid("ls_valid"),
		clk("clk"),
		rst("rst")
	{
		SC_METHOD(left_shift_func);
		sensitive << clk.pos() << rst.pos();
		sensitive << inp << shift_by << valid;
	}
};
