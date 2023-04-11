#include <systemc.h>
#include "const.h"


SC_MODULE(right_shift) {
	sc_in<sc_bv<N>> inp;	
	sc_out<sc_bv<N>> out;
	

	void right_shift_func(){
		sc_bv<N> inp0;
		sc_bv<N> out0;
		int i, j;

		inp0 = inp.read();
		for(i = N-2; i>=0; i++){
			if(i==N-1) out0[i] = 0;
			else out0[i] = inp0[i+1];
		}
		out.write(out0);
	}

	SC_CTOR(right_shift):
		inp("rs_inp"),
		out("rs_out")
	{
		SC_METHOD(right_shift_func);		
	}
};
