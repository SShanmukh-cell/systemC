#include "fa.cpp"

SC_MODULE(N_FullAdder){
	sc_in<sc_bv<1>> a[n_bit], b[n_bit], c_in;
	
        sc_out<sc_bv<1>> c_out;
        sc_out<sc_bv<1>> sum[n_bit];
        sc_in<bool> clk, reset;

	sc_signal<sc_bv<1>> carry[n_bit];

	FullAdder* FA[n_bit];
	int i;

	/*void n_fulladder_func(){
		//c_out.write(carry.read());					
	}*/


	SC_CTOR(N_FullAdder){		
		for(i = 0; i<n_bit; i++){
			FA[i] = new FullAdder(sc_gen_unique_name("FA"));
			FA[i]->a(a[i]);
			FA[i]->b(b[i]);

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
				FA[i]->c_out(carry[i+1]);
			}

			FA[i]->clk(clk);
			FA[i]->reset(reset);
			
		}
		//SC_METHOD(n_fulladder_func);
	}

	/*~N_FullAdder(){
		for(i = 0; i<n_bit; i++){
			delete FA[i];
		}*/	
};



