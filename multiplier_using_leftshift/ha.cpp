#include <systemc.h>


SC_MODULE(half_adder){
	sc_in<sc_bv<N+N+N>> a;
	sc_in<sc_bv<N+N>> b;
        sc_out<sc_bv<N+N+N>> sum;
	sc_in<bool> rst, clk;

	void h_adder(){
		sc_bv<N+N+N> a0 = a.read();    
		sc_bv<N+N+N> b0 = b.read();
		sc_bv<N+N+N> s0;		        
                int i;


		if(rst){
			s0 = 0;
		}
		else {
			s0 = sc_biguint<N+N+N>(a0) + sc_biguint<N+N+N>(b0);    //// i am using this type of direct integer addition so that the connection between the modules doesnt get complicated and none of the carry bits overriden in any scenario/condition.
		}
		sum.write(s0);
	}

	SC_CTOR(half_adder):
		a("ha_a"),
		b("ha_b"),
		sum("ha_sum"),
		rst("ha_rst"),
		clk("ha_clk")
	{
		SC_METHOD(h_adder);
		sensitive << a << b;
		sensitive << clk.pos();
		sensitive << rst.pos();
	}
};
