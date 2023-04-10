//#include "fa.cpp"
#include "fa_nbit.cpp"


SC_MODULE(FA_TEST){

    sc_clock clk;
    sc_signal<bool> reset;
    sc_signal<sc_bv<1>> a[n_bit], b[n_bit], sum[n_bit], c_in;
    sc_signal<sc_bv<1>> c_out;

    // Instantiate the N-bit adder
    sc_trace_file *pTracefile;

    N_FullAdder* adder;


    void stimulus();


    SC_CTOR(FA_TEST):
	    clk("clk", tp)
	{
	    // Connect the signals
	    adder = new N_FullAdder("adder");

            adder->clk(clk);
            adder->reset(reset);

	    for(int i = 0; i< n_bit; i++){
		    adder->a[i](a[i]);
            	    adder->b[i](b[i]);
            	    adder->sum[i](sum[i]);
	    }

	    adder->c_in(c_in);
	    adder->c_out(c_out);


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
		cout << "start" <<endl;
		reset.write(rand() % 2);
		for(int i = 0; i<n_bit;i++){
			a[i].write(rand() % 2);
		        b[i].write(rand() % 2);
		
		}
		c_in.write(rand() % 2);
		cout << "a = ";
		for(int i = n_bit-1; i>=0 ; i--){
			cout << a[i];
		}
		cout << "  ";

		cout << "b = ";
		for(int i = n_bit-1; i>=0 ; i--){
			cout << b[i];
		}
		cout << "  ";
		cout << " c_in = " << c_in.read() << endl;

		cout << "sum = ";
		for(int i = n_bit-1; i>=0 ; i--){
			cout << sum[i];
		}
		cout << " ";

		cout << " c_out = " << c_out.read() << endl;
		cout << " reset = " << reset.read() << endl;
		cout << "end " << endl;
		
		/////////////////////////////////////////  adding singals to waveform ////////////////////////////////////////////////
                sc_bv<n_bit> a0, b0, sum0;

	        pTracefile = sc_create_vcd_trace_file("fa_waveforms");
	        for(int i = 0; i< n_bit; i++){
			a0[i] = a[i].read().get_bit(0);   ///// gets the 0th bit of ith index of a
		        b0[i] = b[i].read().get_bit(0);
		        sum0[i] = sum[i].read().get_bit(0);
	        }

                sc_trace(pTracefile, clk, "clk");
                sc_trace(pTracefile, reset, "reset");
	        sc_trace(pTracefile, a0, "trace_a");
	        sc_trace(pTracefile, b0, "trace_b");
	        sc_trace(pTracefile, sum0, "trace_sum0");
                sc_trace(pTracefile, c_in, "c_in");
                sc_trace(pTracefile, c_out, "c_out");
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		wait(tp);
	}
}


int sc_main(int argc, char* argv[]){
       FA_TEST test("test");
       sc_start(15*tp);
       sc_stop();
       return 0;
} 

