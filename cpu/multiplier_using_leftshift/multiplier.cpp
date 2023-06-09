#include "ha.cpp"

SC_MODULE(multiplier_N) {                            ///  code is flexible in N bit input which can be changed from const.h
	sc_in<sc_biguint<N>> multiplicand;
	sc_in<sc_biguint<N>> multiplier;
	sc_out<sc_biguint<N+N+N>> product;
	sc_in<bool> clk, rst;

	int i, j, k;
	
	sc_signal<sc_biguint<N+N>> ls_out[N];
	sc_signal<sc_biguint<N+N+N>> temp_product[N];
	sc_signal<sc_biguint<N>> shift0[N];
	sc_signal<sc_biguint<N>> valid1[N];


	void multiplier_func(){
		sc_bv<N> temp2;
		temp2 = multiplier.read();    
		sc_bv<N> s0[N];
		sc_bv<N> v1[N];
		
	        for(j = 0; j < N; j++){
			if(j==0) {
				temp_product[j] = 0;  /// for the first bit only temp_product 0, so that one of the input for adder is 0
			}

			if(temp2[j] == 1){            ///  checking for multiplier bit if it is high 
				s0[j] = j;            ///  if high than storing the index of that bit in local varible which will be later used for shift_by in left shift 
				v1[j] = 1;            ///  taking this inorder to make the output of left shift valid only when index of multiplier bit is high. NOTE: valid is active high in left shift module hence making it high here.
			}
			else {
				s0[j] = 0;            /////  or else make the shift_by 0
				v1[j] = 0;            /////  or else make the valid 0
			}
			shift0[j].write(s0[j]);
			valid1[j].write(v1[j]);
		}
	}

	SC_CTOR(multiplier_N):
		multiplicand("mul_multiplicand"),
		multiplier("mul_multiplier"),
		product("mul_product"),
		rst("mul_rst"),
		clk("mul_clk")
	{		
		SC_METHOD(multiplier_func);
		sensitive << clk.pos();
		sensitive << multiplicand << multiplier;
		
		left_shift_N* ls_N[N];                           ///   connecting left shift module 
		for(i = 0; i<N; i++){
			ls_N[i] = new left_shift_N(sc_gen_unique_name("LS"));
			ls_N[i]->clk(clk);
			ls_N[i]->rst(rst);
			ls_N[i]->inp(multiplicand);
			ls_N[i]->valid(valid1[i]);               ///   required because we want only the output of left shift for which multiplier input bit is high  
			ls_N[i]->shift_by(shift0[i]);            ///   shift by index number of multiplier bit which is high 
			ls_N[i]->out(ls_out[i]);		 ///   getting the output of left shift and storing in a signal of vector so that i can add all and get final product.
		}

		half_adder* ha[N];                               ///   connecting adder module so that i can add all outputs of left shift for which the index of multiplier bit is high, and get the final product.
		for(k = 0; k<N; k++){
			ha[k] = new half_adder(sc_gen_unique_name("HA"));
			ha[k]->clk(clk);
			ha[k]->rst(rst);
			
			ha[k]->a(temp_product[k]);               ///   for first iteration input is 0 and for next interations temp_prduct will be the sum of previous results 
			ha[k]->b(ls_out[k]);                     ///   output of left_shift 
			if(k!=N-1) ha[k]->sum(temp_product[k+1]);///   store sum in next address location so that for next interation(k+1) input 1 for sum will be the same as current iteration(k).
			else ha[k]->sum(product);                ///   if its the last iteration(depends on size of input) than store the final sum in product.
		}
	}
};
