#include "greater_equal.cpp"


SC_MODULE(mul) {
	sc_in<sc_biguint<N>> A, B;	
	sc_out<sc_biguint<N>> O;
	

	void mul_func(){
		sc_biguint<N> a0, b0, o0;
		
		a0 = A.read();
		b0 = B.read();

		o0 = a0 * b0;

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
