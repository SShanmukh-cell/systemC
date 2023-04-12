#include "divider.cpp"



SC_MODULE(divider_test){
	sc_signal<sc_biguint<N>> dividend;
	sc_signal<sc_biguint<N>> divisor;
	sc_signal<sc_biguint<N>> Q;
	sc_signal<sc_biguint<N>> R;
	sc_signal<sc_biguint<1>> req;
	sc_signal<sc_biguint<1>> ready, exception;

	sc_signal<bool> rst;
	sc_clock clk;

	sc_trace_file *trace;

	divider_N* div;

	void stimulus();

	SC_CTOR(divider_test):
		clk("clk", tp),
		dividend("div_test_dividend"),
		divisor("div_test_divisor"),
		Q("div_test_Q"),
		R("div_test_R"),
		req("div_test_req"),
		ready("div_test_ready"),
		exception("div_test_exception"),
		rst("div_test_rst")
	{
		div = new divider_N("div");
		div->clk(clk);
		div->rst(rst);
		div->dividend(dividend);
		div->divisor(divisor);
		div->Q(Q);
		div->R(R);
		div->req(req);
		div->ready(ready);
		div->exception(exception);
		

		trace = sc_create_vcd_trace_file("divider_ls");
		sc_trace(trace, dividend, "dividend");
		sc_trace(trace, divisor, "divisor");
		sc_trace(trace, Q, "Q");
		sc_trace(trace, R, "R");
		sc_trace(trace, clk, "clk");
		sc_trace(trace, rst, "rst");
		sc_trace(trace, req, "req");
		sc_trace(trace, ready, "ready");
		sc_trace(trace, exception, "exception");
		
		SC_THREAD(stimulus);
	}

	~divider_test(){
		sc_close_vcd_trace_file(trace);
	}
};

void divider_test::stimulus(){
	/*srand(time(NULL));
	while(true){
		rst.write(rand() % 2);
		dividend.write(rand());
		divisor.write(rand());
		//dividend = 65535;
		//divisor = 6;
		cout << "rst = " << hex << rst.read() << " dividend = " << hex << dividend.read() << " divisor = " << hex << divisor.read() << " Q_dut = " << hex << Q.read() << " R_dut = " << hex << R.read() << endl;
		
		wait(tp);
	}*/
	rst.write(1);
	wait(2*tp);
	rst.write(0);
	req.write(1);
	dividend.write(65535);
	divisor.write(805);
	wait(tp*2);
	req.write(0);
	//wait(); // Wait for any event
        //if (ready.read() == true) {
	cout << "rst = " << hex << rst.read() << " dividend = " << hex << dividend.read() << " divisor = " << hex << divisor.read() << " Q_dut = " << hex << Q.read() << " R_dut = " << hex << R.read() << endl;
	//}

}


int sc_main(int argc, char* argv[]){
	divider_test test("test");
	sc_start(30*tp);
	sc_stop();
	return 0;
}

