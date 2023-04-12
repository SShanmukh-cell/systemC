#include "right_shift.cpp"


SC_MODULE(greater_equal) {
	sc_in<sc_biguint<N>> A, B;	
	sc_out<sc_biguint<1>> G, E;
	

	void greater_equal_func(){
		sc_biguint<N> a0, b0;
		sc_biguint<1> g0, e0;
		a0 = A.read();
		b0 = B.read();
		if(a0 == b0){
			e0 = 1;
		}
		else if(a0 > b0){
			g0 = 1;
		}
		G.write(g0);
		E.write(e0);
	}

	SC_CTOR(greater_equal):
		A("ge_a"),
		B("ge_b"),
		G("ge_g"),
		E("ge_e")
	{
		SC_METHOD(greater_equal_func);		
	}
};
