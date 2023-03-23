#include "fa.cpp"

SC_MODULE(N_FullAdder){
	sc_in<sc_bv<n_bit>> a, b, c_in;
        sc_out<sc_bv<n_bit>> c_out;
        sc_out<sc_bv<n_bit>> sum;
        sc_in<bool> clk, reset;

	sc_bv<n_bit> a0 = a.read();
        sc_bv<n_bit> b0 = b.read();
	sc_bv<n_bit> c0_in = c_in.read();
        sc_bv<n_bit> c0_out, sum0;

	FullAdder* FA[n_bit];

	void n_fulladder_func(){
		int i;
		

		for(i = 0; i < n_bit; i++){
			FA[i]->a(a0[i]);
			FA[i]->b(b0[i]);
			FA[i]->sum(sum0[i]);
			FA[i]->c_out(c0_out[i]);

			if(i==0){
				FA[i]->c_in(c0_in[i]);
			}
			else{
				FA[i]->c_in(c0_out[i-1]);
			}
			
		}
		//sum.write(sum0);
		//c_out.write(co_out);
			
	}

	SC_CTOR(N_FullAdder){
		sc_METHOD(n_fulladder_func);
		//sinsitive << s0 << b0 << c0_in;

		for(i = 0; i<n_bit; i++){
			FA[i] = new FullAdder("FA" + std::to_string(i));
		}
	}

};
