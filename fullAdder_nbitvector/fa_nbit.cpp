#include "fa.cpp"

SC_MODULE(N_FullAdder){
	sc_in<sc_bv<n_bit>> a, b;
        sc_in<sc_bv<1>>	c_in;	
        sc_out<sc_bv<1>> c_out;
        sc_out<sc_bv<n_bit>> sum;
        sc_in<bool> clk, reset;
	
	int i, j, k;

	sc_signal<sc_bv<1>> carry[n_bit];
	sc_signal<sc_bv<1>> sig_a[n_bit], sig_b[n_bit];
        sc_signal<sc_bv<1>> sig_sum[n_bit];


	void n_fulladder_func(){
		sc_bv<n_bit> a0, b0;
		a0 = a.read();
		b0 = b.read();
	        		
		for(j = 0; j < n_bit; j++){
			sig_a[j] = a0[j].get_bit(0);
			sig_b[j] = b0[j].get_bit(0);
		}
	}

	void n_sum_func(){
		sc_bv<n_bit> sum_vec;
		sc_bv<1> sum_temp;
			
		for(k = 0; k < n_bit; k++){
			sum_temp = sig_sum[k];
			sum_vec[k] = sum_temp.get_bit(0);			
		}
		sum.write(sum_vec);
	}

	
	SC_CTOR(N_FullAdder):
		a("faN_a"),
	    	b("faN_b"),
	    	c_in("faN_cin"),
	    	sum("faN_sum"),
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
			FA[i]->a(sig_a[i]);
			FA[i]->b(sig_b[i]);

			if(i==0){
				FA[i]->c_in(c_in);
			}
			else{
				FA[i]->c_in(carry[i]);
				
			}

			FA[i]->sum(sig_sum[i]);

			if(i==n_bit-1){
				FA[i]->c_out(c_out);
			}
			else{
				FA[i]->c_out(carry[i + 1]);
			}

			FA[i]->clk(clk);
			FA[i]->reset(reset);
			
		}

		SC_METHOD(n_sum_func);
		for(int l = 0; l < n_bit; l++){
			sensitive << sig_sum[l];
		}
	}
};



