#include "fs.cpp"

SC_MODULE(N_FullSubtractor){
	sc_in<sc_bv<1>> a[n_bit], b[n_bit], c_in;
	
        sc_out<sc_bv<1>> borrow_out;
        sc_out<sc_bv<1>> difference[n_bit];
        sc_in<bool> clk, reset;

	sc_signal<sc_bv<1>> temp_borrow[n_bit];

	FullSubtractor* FS[n_bit];
	int i;

	/*void n_fulladder_func(){
		//borrow_out.write(temp_borrow.read());					
	}*/


	SC_CTOR(N_FullSubtractor){		
		for(i = 0; i<n_bit; i++){
			FS[i] = new FullSubtractor(sc_gen_unique_name("FS"));
			FS[i]->a(a[i]);
			FS[i]->b(b[i]);

			if(i==0){
				FS[i]->c_in(c_in);
			}
			else{
				FS[i]->c_in(temp_borrow[i]);
				
			}

			FS[i]->difference(difference[i]);

			if(i==n_bit-1){
				FS[i]->borrow_out(borrow_out);
			}
			else{
				FS[i]->borrow_out(temp_borrow[i+1]);
			}

			FS[i]->clk(clk);
			FS[i]->reset(reset);
			
		}
		//SC_METHOD(n_fulladder_func);
	}

	/*~N_FullSubtractor(){
		for(i = 0; i<n_bit; i++){
			delete FS[i];
		}*/	
};



