#include "half_adder.cpp"
#include "const.h"



SC_MODULE(half_adder_test){

	sc_signal<sc_uint<1>> a, b, sum, carry;
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

        srand(time(NULL));
	while(true){
		clr.write(rand() % 2);
		a.write(rand() % 2);
		b.write(rand() % 2);
		cout << " clk = " << clk.read() << " clr = " << clr.read() << " input_a = " << a.read() << " input_b = " << b.read() << " sum = " << sum.read() << " carry = " << carry << endl;
		wait(tp);
	}
}


int sc_main(int agrc, char* argv[]){
	half_adder_test test("h_test");
	sc_start(30*tp);
	sc_stop();
	return 0;
}
