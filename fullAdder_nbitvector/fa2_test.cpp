//#include "fa.cpp"
#include "fa_nbit.cpp"


SC_MODULE(FA_TEST){

    sc_clock clk;
    sc_signal<sc_bv<n_bit>> a, b;
    sc_signal<sc_bv<1>> c_in;
	
    sc_signal<sc_bv<1>> c_out;
    //sc_signal<sc_bv<n_bit>> sum;
    sc_signal<sc_bv<1>> sum[n_bit];
    sc_signal<bool> reset;

    // Instantiate the N-bit adder
    sc_trace_file *pTracefile;

    N_FullAdder* adder;


    void stimulus();


    SC_CTOR(FA_TEST):
	    a("fa_test_a"),
	    b("fa_test_b"),
	    c_in("fa_test_cin"),
	    //sum("fa_test_sum"),
	    c_out("fa_test_c_out"),
	    reset("fa_test_reset"),
	    clk("clk", tp)
	{
	    // Connect the signals
	    adder = new N_FullAdder("adder");

            adder->clk(clk);
            adder->reset(reset);
	    adder->a(a);
            adder->b(b);

	    for(int i = 0; i< n_bit; i++){
		    
            	    adder->sum[i](sum[i]);
	    }
	    //adder->sum(sum);

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
	//reset.write(1);
	int k;
	k = 0;
	while (true){
		//cout << "start" <<endl;
		reset.write(rand() % 2);
		
		a.write(rand() % (1 << n_bit));
		b.write(rand() % (1 << n_bit));
		c_in.write(rand() % 2);
		k++;
		
		

		cout << "********************************  test run " << k << " ***********************************" << endl;
		cout << " " << endl;
		cout << "rst = " << hex << reset.read() << " a = " << hex << a.read() << " b = " << hex << b.read() << " c_in = " << hex << c_in.read() << " c_out = " << hex << c_out.read() << endl;
		
		
		
		cout << "sum = ";
		for(int i = n_bit-1; i>=0 ; i--){
			cout << sum[i];
		}
		cout << " " << endl;
		
		//cout << "end " << endl;
		
		/////////////////////////////////////////  adding singals to waveform ////////////////////////////////////////////////
                sc_bv<n_bit> a0, b0, sum0;

	        pTracefile = sc_create_vcd_trace_file("fa_waveforms");
	        for(int i = 0; i< n_bit; i++){			
		        sum0[i] = sum[i].read().get_bit(0);
	        }

                
	        sc_trace(pTracefile, a, "trace_a");
	        sc_trace(pTracefile, b, "trace_b");
	        sc_trace(pTracefile, sum0, "trace_sum");
		sc_trace(pTracefile, clk, "clk");
                sc_trace(pTracefile, reset, "reset");
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

