#include "multiplier.cpp"



SC_MODULE(multiplier_test){
	sc_signal<sc_biguint<N>> multiplicand;
	sc_signal<sc_biguint<N>> multiplier;
	sc_signal<sc_biguint<N+N+N>> product;
	sc_signal<bool> rst;
	sc_clock clk;

	sc_trace_file *trace;

	multiplier_N* mul;

	void stimulus();

	SC_CTOR(multiplier_test):
		clk("mul_test_clk", tp),
		multiplicand("mul_test_multiplicand"),
		multiplier("mul_test_multiplier"),
		product("mul_test_product"),
		rst("mul_test_rst")
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
	srand(time(NULL));
	while(true){
		rst.write(rand() % 2);
		multiplicand.write(rand());
		multiplier.write(rand());
		cout << "rst = " << hex << rst.read() << " multiplicand = " << hex << multiplicand.read() << " multiplier = " << hex << multiplier.read() << " product_dut = " << hex << product.read() << endl;
		wait(tp);
	}
}


int sc_main(int argc, char* argv[]){
	multiplier_test test("test");
	sc_start(15*tp);
	sc_stop();
	return 0;
}
