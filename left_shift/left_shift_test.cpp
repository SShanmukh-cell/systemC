#include "left_shift.cpp"



SC_MODULE(left_shift_test){
	sc_signal<sc_bv<N>> inp;
	sc_signal<sc_bv<S>> shift_by;
	sc_signal<sc_bv<N+N>> out;
	sc_clock clk;

	sc_trace_file *trace;

	left_shift_N shift_l;

	void stimulus();

	SC_CTOR(left_shift_test):
		shift_l("shift_l"),
		clk("clk", tp)
	{
		shift_l.inp(inp);
		shift_l.shift_by(shift_by);
		shift_l.out(out);
		shift_l.clk(clk);

		trace = sc_create_vcd_trace_file("left_shift");
		sc_trace(trace, inp, "input");
		sc_trace(trace, shift_by, "shift_by");
		sc_trace(trace, out, "output");
		sc_trace(trace, clk, "clk");
		
		SC_THREAD(stimulus);
	}

	~left_shift_test(){
		sc_close_vcd_trace_file(trace);
	}
};

void left_shift_test::stimulus(){
	srand(time(NULL));
	while(true){
		inp.write(rand()/* % (1 << N)*/);
		shift_by.write(rand() % (1 << S));
		cout << "input = " << hex << inp.read() << " shift_r_by = " << hex << shift_by.read() << " output = " << hex << out.read() << endl;
		//cout << "input = " << inp.read() << " shift_r_by = " << shift_by.read() << " output = " << out.read() << endl;
		wait(tp);
	}
}


int sc_main(int argc, char* argv[]){
	left_shift_test test("test");
	sc_start(15*tp);
	sc_stop();
	return 0;
}
