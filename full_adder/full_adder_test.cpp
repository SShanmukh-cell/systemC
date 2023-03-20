#include "full_adder.cpp"


SC_MODULE(full_adder_test){

	sc_signal<sc_bv<bit_length>> a, b, ci, sum;
	sc_signal<bool> clr;
	sc_clock clk;
	sc_signal<sc_logic> carry;

	full_adder adder;

	sc_trace_file *pTracefile;

	void stimulus();

	SC_CTOR(full_adder_test):
		clk("clk", tp),
		adder("adder")
	{
		adder.a(a);
		adder.b(b);
		adder.ci(ci);
		adder.sum(sum);
		adder.carry(carry);
		adder.clr(clr);
		adder.clk(clk);

		pTracefile = sc_create_vcd_trace_file("full_adder_vcd_waves");

		sc_trace(pTracefile, clr, "clear");
		sc_trace(pTracefile, clk, "clk");
		sc_trace(pTracefile, a, "input_a");
                sc_trace(pTracefile, b, "input_b");
		sc_trace(pTracefile, ci, "input_ci");
                sc_trace(pTracefile, sum, "sum");
                sc_trace(pTracefile, carry, "carry");


		SC_THREAD(stimulus)
	}

	~full_adder_test(){
		sc_close_vcd_trace_file(pTracefile);
	}
};


void full_adder_test::stimulus(){

	wait(tp/2);
	
	srand(time(NULL));
	while(true){
		clr.write(rand() % 2);
		a.write(rand() % (1 << bit_length));
		b.write(rand() % (1 << bit_length));
		ci.write(rand() % (1 << bit_length));
		sc_bv<bit_length> third_inp = ci.read();
		
 
		cout << " clr = " << clr.read() << " input_a = " << a.read() << " input_b = " << b.read() << " input_cin = " << third_inp[0] << " sum = " << sum.read() << " carry = " << carry << endl;
		wait(tp);
	}
}


int sc_main(int agrc, char* argv[]){
	full_adder_test test("full_adder_test");
	sc_start(15*tp);
	sc_stop();
	return 0;
}

