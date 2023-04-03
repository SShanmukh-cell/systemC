#include "multiplier.cpp"



SC_MODULE(multiplier_test){
	sc_signal<sc_bv<N>> multiplicand;
	sc_signal<sc_bv<N>> multiplier;
	sc_signal<sc_bv<N+N+N>> product;
	sc_signal<bool> rst;
	sc_clock clk;

	sc_trace_file *trace;

	multiplier_N* mul;

	void stimulus();

	SC_CTOR(multiplier_test):
		clk("clk", tp)
	{
		mul = new multiplier_N("mul");
		mul->clk(clk);
		mul->rst(rst);
		mul->multiplicand(multiplicand);
		mul->multiplier(multiplier);
		mul->product(product);
		

		trace = sc_create_vcd_trace_file("multiplier_ls");
		sc_trace(trace, multiplicand, "multiplicand");
		sc_trace(trace, multiplier, "multiplier");
		sc_trace(trace, product, "productput");
		sc_trace(trace, clk, "clk");
		sc_trace(trace, rst, "rst");
		
		SC_THREAD(stimulus);
	}

	~multiplier_test(){
		sc_close_vcd_trace_file(trace);
	}
};

void multiplier_test::stimulus(){
	/*rst.write(1);
	wait(tp);
	rst.write(0);
	wait(tp);*/
	srand(time(NULL));
	while(true){
		rst.write(0);
		multiplicand = rand() % (1 << N);
		multiplier = rand() % (1 << N);
		cout << "rst = " << hex << rst.read() << " multiplicand = " << hex << multiplicand.read() << " multiplier = " << hex << multiplier.read() << " product = " << hex << product.read() << endl;
		cout << "rst = " << rst.read() << " multiplicand = " << multiplicand.read() << " multiplier = " << multiplier.read() << " product = " << product.read() << endl;
		wait(tp);
	}
}


int sc_main(int argc, char* argv[]){
	multiplier_test test("test");
	sc_start(15*tp);
	sc_stop();
	return 0;
}
