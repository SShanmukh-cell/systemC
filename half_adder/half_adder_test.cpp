#include "half_adder.cpp"


SC_MODULE(half_adder_test){

	sc_signal<sc_bv<data_width>> a, b, sum;
        sc_signal<sc_logic> carry;
	sc_signal<bool> clr;
	sc_clock clk;

	sc_trace_file *pTracefile;

	half_adder adder;

	void stimulus();

	SC_CTOR(half_adder_test):
		adder("adder"),
		clk("clk", tp)
	{
		adder.a(a);
		adder.b(b);
		adder.sum(sum);
		adder.carry(carry);
		adder.clk(clk);
		adder.clr(clr);

		pTracefile = sc_create_vcd_trace_file("half_adder_vcd_waves");

		sc_trace(pTracefile, clr, "clear");
		sc_trace(pTracefile, clk, "clk");
		sc_trace(pTracefile, a, "input_a");
                sc_trace(pTracefile, b, "input_b");
                sc_trace(pTracefile, sum, "sum");
                sc_trace(pTracefile, carry, "carry");

		SC_THREAD(stimulus)

	}

	~half_adder_test(){
		sc_close_vcd_trace_file(pTracefile);
	}
};


void half_adder_test::stimulus(){

	wait(tp/2);
        srand(time(NULL));
	while(true){
		clr.write(rand() % 2);
		a.write(rand() % (1 << data_width));      ///// 1 << data_width is nothing but: 1 * 2^data_width: will give me random valuw between 0 to 2^datawidth-1 
		b.write(rand() % (1 << data_width));       ///////// if data _width is 4 than : randomize between 0 to 2^4-1 i.e 0 to 15 
		cout << " clr = " << clr.read() << " input_a = " << a.read() << " input_b = " << b.read() << " sum = " << sum.read() << " carry = " << carry << endl;
		wait(tp);
	}
}


int sc_main(int agrc, char* argv[]){
	half_adder_test test("h_test");
	sc_start(15*tp);
	sc_stop();
	return 0;
}
