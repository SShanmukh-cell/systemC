#include "greater_equal.cpp"


SC_MODULE(mul) {
	sc_in<sc_bv<N>> A, B;	
	sc_out<sc_bv<N>> O;
	

	void mul_func(){
		sc_bv<N> a0, b0, o0;
		
		a0 = A.read();
		b0 = B.read();

		o0 = sc_biguint<N>(a0) * sc_biguint<N>(b0);

		O.write(o0);
	}

	SC_CTOR(mul):
		A("mul_a"),
		B("mul_b"),
		O("mul_o")
	{
		SC_METHOD(mul_func);		
	}
};
