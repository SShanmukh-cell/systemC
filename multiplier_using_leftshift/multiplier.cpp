#include "left_shift.cpp"
#include "ha.cpp"

SC_MODULE(multiplier_N) {
	sc_in<sc_bv<N>> multiplicand;
	sc_in<sc_bv<N>> multiplier;
	sc_out<sc_bv<N+N+N>> product;
	sc_in<bool> clk, rst;

	int i, j, k, l;
	//sc_signal<sc_bv<N+N>> store1[N];
			
	
	//left_shift_N ls_N;


	
	//sc_signal<sc_bv<N+N>> store0[N];
	//sc_signal<sc_bv<N+N>> c0[N];
	sc_signal<sc_bv<N+N>> c1[N];
	sc_signal<sc_bv<N+N+N>> temp_product;
	sc_signal<sc_bv<N>> shift0[N];
	sc_signal<sc_bv<N>> shift1[N];


	void multiplier_func(){
		cout << "multiplier function " << endl;
		sc_bv<N> temp2;
		temp2 = multiplier.read();
		cout << "temp2 = " << multiplier.read() << endl;
		sc_bv<N> s0[N];
		
	        for(j = 0; j < N; j++){			
			if(temp2[j] == 1){
				s0[j] = j;
			}
			else {
				s0[j] = 0;
			}
			shift0[j].write(s0[j]);
			cout << "s0[" << j << "] = " << s0[j] << endl;
		}
		/*for(l = 0; l<N; l++){
			cout << "c1[" << l << "] = " << c1[l] << endl;		
		}



		sc_bv<N+N> temp_product0;

		for(k = 0; k < N; k++){			
			if(temp2[k] == 1){
				temp_product0 = c1[k].read();
				
			}
			else {
				temp_product0 = 0;
				//temp_product.write(sc_biguint<N+N>(temp_product.read()) + 0);
			}
			temp_product.write(sc_biguint<N+N>(temp_product.read()) + sc_biguint<N+N>(temp_product0));
		}
		cout << "temp_product" << temp_product.read() << endl;
		if(rst) product.write(0);
		else product.write(temp_product);*/
	}

	SC_CTOR(multiplier_N){		
		SC_METHOD(multiplier_func);
		//sensitive << clk.pos();
		sensitive << multiplicand << multiplier;
		

	

		left_shift_N* ls_N[N];
		for(i = 0; i<N; i++){
			ls_N[i] = new left_shift_N(sc_gen_unique_name("LS"));
			ls_N[i]->clk(clk);
			ls_N[i]->rst(rst);
			ls_N[i]->inp(multiplicand);
			ls_N[i]->shift_by(shift0[i]);
			ls_N[i]->out(c1[i]);		
		}

		half_adder* ha[N];
		for(k = 0; k<N; k++){
			ha[k] = new half_adder(sc_gen_unique_name("HA"));
			ha[k]->clk(clk);
			ha[k]->rst(rst);
			ha[k]->a(temp_product);
			ha[k]->b(c1[k]);
			if(k!=N-1) ha[k]->sum(temp_product);
			else ha[k]->sum(product);	
		}
		

		//SC_METHOD(product_func);
		//sensitive << multiplicand;
		//sensitive << clk.pos();
	}


	/*void product_func() {
		sc_bv<N> temp1;
		temp1 = multiplier.read();
		temp_product.write(0);
		sc_bv<N+N> c0[N];
		sc_bv<N+N> temp_product0;
		cout << "temp1 = " << temp1 << endl;


		for(k = 0; k < N; k++){			
			if(multiplier.read()[k] == 1){
				temp_product0 = c1[k].read();
				
			}
			else {
				temp_product0 = 0;
				//temp_product.write(sc_biguint<N+N>(temp_product.read()) + 0);
			}
			temp_product.write(sc_biguint<N+N>(temp_product.read()) + sc_biguint<N+N>(temp_product0));
		}
		cout << "temp_product" << temp_product.read() << endl;
		if(rst) product.write(0);
		else product.write(temp_product);*/
	//}
};
