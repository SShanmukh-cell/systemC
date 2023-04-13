#include "right_shift.cpp"



SC_MODULE(right_shift_test){
	sc_signal<sc_bv<N>> inp;
	sc_signal<sc_bv<S>> shift_by;
	sc_signal<sc_bv<N>> out;
	sc_clock clk;

	sc_trace_file *trace;

	right_shift_N shift_r;

	void stimulus();

	SC_CTOR(right_shift_test):
		shift_r("shift_r"),
		clk("clk", tp)
	{
		shift_r.inp(inp);
		shift_r.shift_by(shift_by);
		shift_r.out(out);
		shift_r.clk(clk);

		trace = sc_create_vcd_trace_file("right_shift");
		sc_trace(trace, inp, "input");
		sc_trace(trace, shift_by, "shift_by");
		sc_trace(trace, out, "output");
		sc_trace(trace, clk, "clk");
		
		SC_THREAD(stimulus);
	}

	~right_shift_test(){
		sc_close_vcd_trace_file(trace);
	}
};

void right_shift_test::stimulus(){
	srand(time(NULL));
	while(true){
		inp.write(rand() );
		shift_by.write(rand() % (1 << S));
		cout << "input = " << inp.read() << " shift_r_by = " << shift_by.read() << " output = " << out.read() << endl;
		wait(tp);
	}
}


int sc_main(int argc, char* argv[]){
	right_shift_test test("test");
	sc_start(15*tp);
	sc_stop();
	return 0;
}
