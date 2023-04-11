#include "sub.cpp"


SC_MODULE(add) {
	sc_in<sc_bv<N>> A, B;	
	sc_out<sc_bv<N>> O;
	

	void add_func(){
		sc_bv<N> a0, b0, o0;
		
		a0 = A.read();
		b0 = B.read();

		o0 = sc_biguint<N>(a0) + sc_biguint<N>(b0);

		O.write(o0);
	}

	SC_CTOR(add):
		A("add_a"),
		B("add_b"),
		O("add_o")
	{
		SC_METHOD(add_func);		
	}
};
