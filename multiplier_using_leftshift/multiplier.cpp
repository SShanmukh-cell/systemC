#include "left_shift.cpp"

SC_MODULE(multiplier_N) {
	sc_in<sc_bv<N>> multiplicand;
	sc_in<sc_bv<N>> multiplier;
	sc_out<sc_bv<N+N>> product;
	sc_in<bool> clk;

	int i, j;
	sc_signal<sc_bv<N+N>> store, temp_product;
	sc_signal<sc_bv<4>> shift;
	sc_signal<sc_bv<N>> inp1;
	sc_bv<N> inp2;

	left_shift_N* ls;

	void multiplier_func(){
		product.write(temp_product);		
	}

	SC_CTOR(multiplier_N){
		inp1 = multiplicand.read();
		inp2 = multiplier.read();
		temp_product = 0;
		for(i = 0; i < N; i++){
			ls = new left_shift_N(sc_gen_unique_name("LS"));
			
			if(inp2[i] != 0b0){
				shift = i;
			}
			else{
				shift = 0;
			}

			ls->inp(multiplicand);
			ls->shift_by(shift);
			ls->out(store);
			ls->clk(clk);

			temp_product.write(sc_biguint<N+N>(temp_product.read()) + sc_biguint<N+N>(store.read()));
			//temp_product = temp_product.read() + store.read();
		}

		SC_METHOD(multiplier_func);
		sensitive << clk.pos();
		sensitive << multiplicand << multiplier;
	}
};
