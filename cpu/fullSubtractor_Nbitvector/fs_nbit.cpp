#include "fs.cpp"

SC_MODULE(N_FullSubtractor){
	sc_in<sc_bv<n_bit>> a, b;
	sc_in<sc_bv<1>> c_in;
	
        sc_out<sc_bv<1>> borrow_out;
        sc_out<sc_bv<n_bit>> difference;
        sc_in<bool> clk, reset;

	sc_signal<sc_bv<1>> temp_borrow[n_bit];
	sc_signal<sc_bv<1>> sig_a[n_bit], sig_b[n_bit];
        sc_signal<sc_bv<1>> sig_difference[n_bit];
	
	int i, j, k;

	void n_fullSubtractor_func(){                             ///  in this function i am reading the input and writing to some local variable and again reading the varible and writing to signal which is an array 
		sc_bv<n_bit> a0, b0;
		a0 = a.read();
		b0 = b.read();
	        		
		for(j = 0; j < n_bit; j++){
			sig_a[j] = a0[j].get_bit(0);          //  get the jth bit from a variable and write to signal so that we can do bit by bit subtractor operation
			sig_b[j] = b0[j].get_bit(0);
		}
	}

	void n_difference_func(){                                //// in this function i am reading the difference signal value storing in 1 bit temp difference and again reading the temp_diff writing to difference(in vector), and finallly writing the complete vector difference to output port difference
		sc_bv<n_bit> difference_vec;
		sc_bv<1> difference_temp;
			
		for(k = 0; k < n_bit; k++){
			difference_temp = sig_difference[k];
			difference_vec[k] = difference_temp.get_bit(0);			
		}
		difference.write(difference_vec);
	}


	SC_CTOR(N_FullSubtractor):
		a("fsN_a"),
	    	b("fsN_b"),
	    	c_in("fsN_c_in"),
	    	difference("fsN_difference"),
	    	borrow_out("fsN_borrow"),
	    	clk("fsN_clk"),
	    	reset("fsN_reset")
	{

		SC_METHOD(n_fullSubtractor_func);      // function is sensitive to pos-clk, pos-reset, and input a, b, cin
		sensitive << clk.pos();
		sensitive << reset.pos();
		sensitive << a << b << c_in;

		
		FullSubtractor* FS[n_bit];
		for(i = 0; i<n_bit; i++){
			FS[i] = new FullSubtractor(sc_gen_unique_name("FS"));
			FS[i]->a(sig_a[i]);
			FS[i]->b(sig_b[i]);

			if(i==0){
				FS[i]->c_in(c_in);
			}
			else{
				FS[i]->c_in(temp_borrow[i]);
				
			}

			FS[i]->difference(sig_difference[i]);

			if(i==n_bit-1){
				FS[i]->borrow_out(borrow_out);
			}
			else{
				FS[i]->borrow_out(temp_borrow[i+1]);
			}

			FS[i]->clk(clk);
			FS[i]->reset(reset);
			
		}
		SC_METHOD(n_difference_func);
		for(int l = 0; l < n_bit; l++){       //  function is sensitive to only difference signal which is an array
			sensitive << sig_difference[l];
		}
	}

};



