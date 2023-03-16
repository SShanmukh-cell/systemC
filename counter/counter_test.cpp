#include "counter.h"
//#include <systemc.h>

SC_MODULE(counter_test){
	sc_signal<bool> clk;
        sc_signal<bool>	clr;
	sc_signal<sc_uint<4>> count;

	sc_trace_file *pTracefile;

	counter cnt;

	void stimulus();

	SC_CTOR(counter_test):
		/*clk("sig_clk"),
		clr("sig_clr"),
		count("sig_count"),*/
		cnt("counter")
	{
		cnt.clk(clk);
		cnt.clr(clr);
		cnt.count(count);

		pTracefile = sc_create_vcd_trace_file("counter_vcd_waves");

                sc_trace(pTracefile, clk, "trace_clk");
                sc_trace(pTracefile, clr, "trace_clr");
                sc_trace(pTracefile, count, "trace_count");

		SC_THREAD(stimulus)
	}

	~counter_test(){
		sc_close_vcd_trace_file(pTracefile);
	}
};


void counter_test::stimulus(){

	clr.write(true);
 
	int i;
	for(i = 0; i<=4; i++){
		clk.write(true);
		wait(5, SC_NS);
		clk.write(false);
		wait(5, SC_NS);
	}
	
	clr.write(false);

	for(i = 0; i<=19; i++){
		clk.write(true);
		wait(5, SC_NS);
		clk.write(false);
		wait(5, SC_NS);
	}
	
	clr.write(true);

        for(i = 0; i<=4; i++){
		clk.write(true);
		wait(5, SC_NS);
		clk.write(false);
		wait(5, SC_NS);
	}
	
	clr.write(false);

	for(i = 0; i<=19; i++){
		clk.write(true);
		wait(5, SC_NS);
		clk.write(false);
		wait(5, SC_NS);
	}
	//sc_stop();
}


int sc_main(int argc, char* argv[]){
	counter_test test("counter_test");
	sc_start();
	return 0;
}

