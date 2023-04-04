#include "left_shift.cpp"
#include "ha.cpp"

SC_MODULE(multiplier_N) {
	sc_in<sc_bv<N>> multiplicand;
	sc_in<sc_bv<N>> multiplier;
	sc_out<sc_bv<N+N+N>> product;
	sc_in<bool> clk, rst;

	int i, j, k;
	
	sc_signal<sc_bv<N+N>> c1[N];
	sc_signal<sc_bv<N+N+N>> temp_product[N];
	sc_signal<sc_bv<N>> shift0[N];
	sc_signal<sc_bv<N>> valid1[N];


	void multiplier_func(){
		sc_bv<N> temp2;
		temp2 = multiplier.read();
		sc_bv<N> s0[N];
		sc_bv<N> v1[N];
		
	        for(j = 0; j < N; j++){
			if(j==0) {
				temp_product[j] = 0;  /// for the first bit only temp_product 0, so that one of the input for adder is 0
			}

			if(temp2[j] == 1){
				s0[j] = j;
				v1[j] = 1;        ///  taking this inorder to make the output of left shift valid only when index of multiplier bit is taken. remeber that valid is active high in left shift module hence making it high here.
			}
			else {
				s0[j] = 0;
				v1[j] = 0;         ////  or else make the valid 0
			}
			shift0[j].write(s0[j]);
			valid1[j].write(v1[j]);
			//cout << "s0[" << j << "] = " << s0[j] << endl;
			//cout << "v1[" << j << "] = " << v1[j] << endl;
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
		
		left_shift_N* ls_N[N];       //// connecting left shift module 
		for(i = 0; i<N; i++){
			ls_N[i] = new left_shift_N(sc_gen_unique_name("LS"));
			ls_N[i]->clk(clk);
			ls_N[i]->rst(rst);
			ls_N[i]->inp(multiplicand);
			ls_N[i]->valid(valid1[i]);
			ls_N[i]->shift_by(shift0[i]);
			ls_N[i]->out(c1[i]);		
		}

		half_adder* ha[N];     /// connecting adder module so that i can add all outputs of left shift for which the index of multiplier bit is high, and get the final product.
		for(k = 0; k<N; k++){
			ha[k] = new half_adder(sc_gen_unique_name("HA"));
			ha[k]->clk(clk);
			ha[k]->rst(rst);
			
			ha[k]->a(temp_product[k]);
			ha[k]->b(c1[k]);
			if(k!=N-1) ha[k]->sum(temp_product[k+1]);
			else ha[k]->sum(product);
		}
	}
};
