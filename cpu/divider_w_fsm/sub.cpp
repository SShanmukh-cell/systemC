


SC_MODULE(sub) {
	sc_in<sc_biguint<N>> A, B;	
	sc_out<sc_biguint<N>> O;
	

	void sub_func(){
		sc_biguint<N> a0, b0, o0;
		
		a0 = A.read();
		b0 = B.read();

		o0 = a0 - b0;

		O.write(o0);
	}

	SC_CTOR(sub):
		A("sub_a"),
		B("sub_b"),
		O("sub_o")
	{
		SC_METHOD(sub_func);	
		sensitive << A << B;	
	}
};
