#include <systemc.h>
#include "const.h"


SC_MODULE(left_shift_N) {
	sc_in<sc_bv<N>> inp;
	sc_in<sc_bv<N>> shift_by;
	sc_out<sc_bv<N+N>> out;
	sc_in<bool> clk, rst;

	void left_shift_func(){
		sc_bv<N+N> temp0;
		sc_bv<N> shift0;
		int i, j;

		shift0 = shift_by.read();
		if(rst){
			out.write(0);
		}
		else {
			if(shift0 == 0b0){
				out.write(inp.read());
			}
			else {
				temp0 = inp.read();
			
				sc_uint<N> s;
				s = shift0;
				for(j = N-1; j >= 0; j--){
					temp0[j+s] = temp0[j];
					if(j==0) {
						for(i = s-1; i >= 0; i--){
							temp0[i] = 0;
						}
					}
				}			
				out.write(temp0);
			}
		}			
	}

	SC_CTOR(left_shift_N){
		SC_METHOD(left_shift_func);
		sensitive << clk.pos();
		sensitive << inp << shift_by;
	}
};
