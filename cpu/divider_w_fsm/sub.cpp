#include "mul.cpp"


SC_MODULE(sub) {
	sc_in<sc_bv<N>> A, B;	
	sc_out<sc_bv<N>> O;
	

	void sub_func(){
		sc_bv<N> a0, b0, o0;
		
		a0 = A.read();
		b0 = B.read();

		o0 = sc_biguint<N>(a0) - sc_biguint<N>(b0);

		O.write(o0);
	}

	SC_CTOR(sub):
		A("sub_a"),
		B("sub_b"),
		O("sub_o")
	{
		SC_METHOD(sub_func);		
	}
};
