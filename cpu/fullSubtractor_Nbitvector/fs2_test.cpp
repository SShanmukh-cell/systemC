#include "fs_nbit.cpp"



SC_MODULE(FS_TEST){

    sc_clock clk;
    sc_signal<sc_bv<n_bit>> a, b;
    sc_signal<sc_bv<1>> c_in;	
    sc_signal<sc_bv<1>> borrow_out;
    sc_signal<sc_bv<n_bit>> difference;
    sc_signal<bool> reset;

    // Instantiate the N-bit adder
    sc_trace_file *pTracefile;

    N_FullSubtractor* adder;


    void stimulus();


    SC_CTOR(FS_TEST):
	    a("fa_test_a"),
	    b("fa_test_b"),
	    c_in("fa_test_cin"),
	    difference("fa_test_difference"),
	    borrow_out("fa_test_borrow_out"),
	    reset("fa_test_reset"),
	    clk("clk", tp)
	{
	    // Connect the signals
	    adder = new N_FullSubtractor("adder");

            adder->clk(clk);
            adder->reset(reset);
	    adder->a(a);
            adder->b(b);	    
	    adder->difference(difference);
	    adder->c_in(c_in);
	    adder->borrow_out(borrow_out);



	    /////////////////////////////////////////  adding singals to waveform ////////////////////////////////////////////////
                
	    pTracefile = sc_create_vcd_trace_file("Nbit_full_Subtractor_waves");
                
	    sc_trace(pTracefile, a, "trace_a");
	    sc_trace(pTracefile, b, "trace_b");
	    sc_trace(pTracefile, difference, "trace_difference");
	    sc_trace(pTracefile, clk, "clk");
            sc_trace(pTracefile, reset, "reset");
            sc_trace(pTracefile, c_in, "c_in");
            sc_trace(pTracefile, borrow_out, "borrow_out");
	    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	    SC_THREAD(stimulus);
    }

    ~FS_TEST(){
	    sc_close_vcd_trace_file(pTracefile);
	    
    }
};	


void FS_TEST::stimulus(){
	
	//wait(tp/2);
	srand(time(NULL));	
	int k;
	k = 0;
	while (true){		
		reset.write(rand() % 2);
		
		a.write(rand() % (1 << n_bit));
		b.write(rand() % (1 << n_bit));
		c_in.write(rand() % 2);
		k++;
		
		cout << " " << endl;
		cout << "********************************  test run " << k << " ***********************************" << endl;
		cout << " " << endl;
		cout << "rst = " << reset.read() << "; a = " << a.read() << "; b = " << b.read() << "; c_in = " << c_in.read() << "; difference = " << difference.read() << "; borrow_out = " << borrow_out.read() << endl;
				
		wait(tp);
	}
}


int sc_main(int argc, char* argv[]){
       FS_TEST test("test");
       sc_start(15*tp);
       sc_stop();
       return 0;
} 

