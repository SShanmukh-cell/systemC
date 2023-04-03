#include <systemc.h>


SC_MODULE(half_adder){
	sc_in<sc_bv<N+N+N>> a;
	sc_in<sc_bv<N+N>> b;
        sc_out<sc_bv<N+N+N>> sum;
	sc_in<bool> rst, clk;

	void h_adder(){
		sc_bv<N+N+N> a0 = a.read();   /// 
		sc_bv<N+N+N> b0 = b.read();
		sc_bv<N+N+N> s0;		        
                int i;


		if(rst){
			sum.write(0);
			//carry.write(SC_LOGIC_0);  /// if the data type is sc_logic that writing false or 0 will throw an error, so we give SC_LOGIC_0/SC_LOGIC_1/SC_LOGIC_X/SC_LOGIC_Z
		}
		else {
			//for( i = 0; i < N; i++){
				s0 = sc_biguint<N+N+N>(a0) + sc_biguint<N+N+N>(b0);
			//}
	
			sum.write(s0);
		}
	}

	SC_CTOR(half_adder){
		SC_METHOD(h_adder);
		sensitive << a << b;
		sensitive << clk.pos();
		//sensitive << rst.pos();
	}
};
