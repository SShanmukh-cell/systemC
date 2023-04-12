#include <systemc.h>
#include "const.h"


SC_MODULE(right_shift) {
	sc_in<sc_biguint<N>> inp;	
	sc_out<sc_biguint<N>> out;
	
	sc_signal<sc_biguint<N>> sig_out;

	void right_shift_func(){
		sc_bv<N> inp0;
		sc_bv<N> out0;
		int i, j;

		inp0 = inp.read();
		for(i = N-1; i>=0; i--){
			if(i==N-1) out0[i] = 0;
			else out0[i] = inp0[i+1];
		}
		sig_out.write(out0);
		out.write(sig_out);
	}

	SC_CTOR(right_shift):
		inp("rs_inp"),
		out("rs_out")
	{
		SC_METHOD(right_shift_func);		
	}
};
