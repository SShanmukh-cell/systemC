


SC_MODULE(right_shift) {
	sc_in<sc_biguint<N>> inp;	
	sc_out<sc_biguint<N>> out;


	void right_shift_func(){
		sc_biguint<N> inp0 = inp.read();
		out.write((0, inp0.range(N-1, 1)));
	}

	SC_CTOR(right_shift):
		inp("rs_inp"),
		out("rs_out")
	{
		SC_METHOD(right_shift_func);	
		sensitive << inp;	
	}
};
