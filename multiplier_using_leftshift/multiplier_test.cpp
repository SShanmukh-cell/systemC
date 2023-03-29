
#include "multiplier.cpp"



SC_MODULE(multiplier_test){
	sc_signal<sc_bv<N>> multiplicand;
	sc_signal<sc_bv<N>> multiplier;
	sc_signal<sc_bv<N+N>> product;
	sc_clock clk;

	sc_trace_file *trace;

	multiplier_N mul;

	void stimulus();

	SC_CTOR(multiplier_test):
		mul("mul"),
		clk("clk", tp)
	{
		mul.multiplicand(multiplicand);
		mul.multiplier(multiplier);
		mul.product(product);
		mul.clk(clk);

		trace = sc_create_vcd_trace_file("multiplier_ls");
		sc_trace(trace, multiplicand, "multiplicand");
		sc_trace(trace, multiplier, "multiplier");
		sc_trace(trace, product, "productput");
		sc_trace(trace, clk, "clk");
		
		SC_THREAD(stimulus);
	}

	~multiplier_test(){
		sc_close_vcd_trace_file(trace);
	}
};

void multiplier_test::stimulus(){
	srand(time(NULL));
	while(true){
		multiplicand.write(rand() % (1 << N));
		multiplier.write(rand() % (1 << 4));
		cout << "multiplicandut = " << hex << multiplicand.read() << " shift_r_by = " << hex << multiplier.read() << " productput = " << hex << product.read() << endl;
		//cproduct << "multiplicandut = " << multiplicand.read() << " shift_r_by = " << multiplier.read() << " productput = " << product.read() << endl;
		wait(tp);
	}
}


int sc_main(int argc, char* argv[]){
	multiplier_test test("test");
	sc_start(15*tp);
	sc_stop();
	return 0;
}
