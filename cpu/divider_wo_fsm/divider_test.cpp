#include "divider.cpp"



SC_MODULE(divider_test){
	sc_signal<sc_biguint<N>> dividend;
	sc_signal<sc_biguint<N>> divisor;
	sc_signal<sc_biguint<N>> quotient;
	sc_signal<sc_biguint<N>> remainder;

	sc_signal<bool> rst;
	sc_clock clk;

	sc_trace_file *trace;

	divider_N* div;

	void stimulus();

	SC_CTOR(divider_test):
		clk("clk", tp),
		dividend("div_test_dividend"),
		divisor("div_test_divisor"),
		quotient("div_test_quotient"),
		remainder("div_test_remainder"),
		rst("div_test_rst")
	{
		div = new divider_N("div");
		div->clk(clk);
		div->rst(rst);
		div->dividend(dividend);
		div->divisor(divisor);
		div->quotient(quotient);
		div->remainder(remainder);
		

		trace = sc_create_vcd_trace_file("divider_ls");
		sc_trace(trace, dividend, "dividend");
		sc_trace(trace, divisor, "divisor");
		sc_trace(trace, quotient, "quotient");
		sc_trace(trace, remainder, "remainder");
		sc_trace(trace, clk, "clk");
		sc_trace(trace, rst, "rst");
		
		SC_THREAD(stimulus);
	}

	~divider_test(){
		sc_close_vcd_trace_file(trace);
	}
};

void divider_test::stimulus(){
	srand(time(NULL));
	while(true){
		rst.write(rand() % 2);
		dividend.write(rand());
		divisor.write(rand());
		//dividend = 65535;
		//divisor = 6;
		cout << "rst = " << hex << rst.read() << " dividend = " << hex << dividend.read() << " divisor = " << hex << divisor.read() << " quotient_dut = " << hex << quotient.read() << " remainder_dut = " << hex << remainder.read() << endl;
		
		wait(tp);
	}
}


int sc_main(int argc, char* argv[]){
	divider_test test("test");
	sc_start(10*tp);
	sc_stop();
	return 0;
}
