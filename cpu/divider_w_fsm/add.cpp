//#include "sub.cpp"


SC_MODULE(add) {
	sc_in<sc_biguint<N>> A, B;	
	sc_out<sc_biguint<N>> O;
	

	void add_func(){
		sc_biguint<N> a0, b0, o0;
		
		a0 = A.read();
		b0 = B.read();

		o0 = a0 + b0;

		O.write(A.read() + B.read());
	}

	SC_CTOR(add):
		A("add_a"),
		B("add_b"),
		O("add_o")
	{
		SC_METHOD(add_func);	
		sensitive << A << B;	
	}
};
