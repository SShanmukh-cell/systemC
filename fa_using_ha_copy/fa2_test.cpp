//#include "fa.cpp"
#include "fa_nbit.cpp"


SC_MODULE(FA_TEST){

    sc_clock clk;
    sc_signal<bool> reset;
    sc_signal<sc_bv<1>> a, b, sum, c_in, c_out;

    // Instantiate the N-bit adder
    //NBitAdder n_bit_adder("n_bit_adder");
    //
    sc_trace_file *pTracefile;


    //FullAdder* adder = new FullAdder("adder");
    N_FullAdder* adder = new N_FullAdder("adder");


    void stimulus();


    SC_CTOR(FA_TEST):
	    clk("clk", tp)
	{
	    // Connect the signals
            adder->clk(clk);
            adder->reset(reset);
            adder->a(a);
            adder->b(b);
            adder->sum(sum);
            adder->c_in(c_in);
            adder->c_out(c_out);

            // Open VCD file
            pTracefile = sc_create_vcd_trace_file("waveforms");
	    
            sc_trace(pTracefile, clk, "clk");
            sc_trace(pTracefile, reset, "reset");
            sc_trace(pTracefile, a, "a");
            sc_trace(pTracefile, b, "b");
            sc_trace(pTracefile, sum, "sum");
            sc_trace(pTracefile, c_in, "c_in");
            sc_trace(pTracefile, c_out, "c_out");

	    SC_THREAD(stimulus);
    }

    ~FA_TEST(){
	    sc_close_vcd_trace_file(pTracefile);
	    
    }
};


void FA_TEST::stimulus(){

	
	//wait(tp/2);
	srand(time(NULL));
	while (true){
		reset.write(rand() % 2);
		a.write(rand() % (1<<n_bit));
		b.write(rand() % (1<<n_bit));
		c_in.write(rand() % (1<<n_bit));
		//inp.write(95);
		//cout << "Input is " << inp.read() << ", FIR filter output is " << outp.read() << endl;
		cout << "a = " << a.read() << " b = " << b.read() << " c_in = " << c_in.read() << " sum = " << sum.read() << " c_out = " << c_out.read() << endl;
		wait(tp);
	}
}


int sc_main(int argc, char* argv[]){
       FA_TEST test("test");
       sc_start(15*tp);
       sc_stop();
       return 0;
} 

