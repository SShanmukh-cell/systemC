#include "fa.cpp"

SC_MODULE(N_FullAdder){
	sc_in<sc_bv<n_bit>> a, b;
        sc_in<sc_bv<1>>	c_in;
	
        sc_out<sc_bv<1>> c_out;
        //sc_out<sc_bv<n_bit>> sum;
	sc_out<sc_bv<1>> sum[n_bit];
        sc_in<bool> clk, reset;

	sc_signal<sc_bv<1>> carry[n_bit];

	

	
	int i, j, k;

	sc_signal<sc_bv<1>> as[n_bit], bs[n_bit];
	sc_signal<sc_bv<1>> cs_in;	
        sc_signal<sc_bv<1>> cs_out;
        sc_signal<sc_bv<1>> sums[n_bit];
	sc_signal<sc_bv<n_bit>> sum_temp;

	void n_fulladder_func(){
		sc_bv<n_bit> a0, b0;
		a0 = a.read();
		b0 = b.read();
	        
		
		for(j = 0; j < n_bit; j++){
			as[j] = a0[j].get_bit(0);
			bs[j] = b0[j].get_bit(0);
		}
	}

	
	SC_CTOR(N_FullAdder):
		a("faN_a"),
	    	b("faN_b"),
	    	c_in("faN_cin"),
	    	//sum("faN_sum"),
	    	c_out("faN_c_out"),
	    	clk("faN_clk"),
	    	reset("faN_reset")
	{
		SC_METHOD(n_fulladder_func);
		sensitive << clk.pos();
		sensitive << reset.pos();
		sensitive << a << b << c_in;


		FullAdder* FA[n_bit];
		for(i = 0; i<n_bit; i++){
			FA[i] = new FullAdder(sc_gen_unique_name("FA"));
			FA[i]->a(as[i]);
			FA[i]->b(bs[i]);

			if(i==0){
				FA[i]->c_in(c_in);
			}
			else{
				FA[i]->c_in(carry[i]);
				
			}

			FA[i]->sum(sum[i]);

			if(i==n_bit-1){
				FA[i]->c_out(c_out);
			}
			else{
				FA[i]->c_out(carry[i + 1]);
			}

			FA[i]->clk(clk);
			FA[i]->reset(reset);
			
		}
		
	}

};



