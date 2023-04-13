#include <systemc.h>
#include <iomanip>
#include "const.h"

SC_MODULE(right_shift_N) {
	sc_in<sc_bv<N>> inp;
	sc_in<sc_bv<S>> shift_by;
	sc_out<sc_bv<N>> out;
	sc_in<bool> clk;

	void right_shift_func(){
		sc_bv<N> inp0;
		sc_bv<S> shift0;
		int i, j;

		shift0 = shift_by.read();

		if(shift0 == 0b0){
			out.write(inp.read());
		}
		else {
			inp0 = inp.read();
			
			sc_uint<S> s;
			s = shift0;
			for(i = 0; i < s; i++){
				for(j = 0; j < N; j++){
					if(j!=N-1){
						inp0[j] = inp0[j+1];
					}
					else {
						inp0[j] = 0;
					}
				}
			}
			out.write(inp0);
		}			
	}

	SC_CTOR(right_shift_N){
		SC_METHOD(right_shift_func);
		sensitive << clk.pos();
		sensitive << inp << shift_by;
	}
};
