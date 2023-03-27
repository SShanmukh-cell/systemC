//#include "fs.cpp"
#include "fs_nbit.cpp"


SC_MODULE(FS_TEST){

    sc_clock clk;
    sc_signal<bool> reset;
    sc_signal<sc_bv<1>> a[n_bit], b[n_bit], difference[n_bit], c_in;
    sc_signal<sc_bv<1>> borrow_out;

    // Instantiate the N-bit subtractor
    sc_trace_file *pTracefile;

    N_FullSubtractor* subtractor;


    int i;
    void stimulus();


    SC_CTOR(FS_TEST):
	    clk("clk", tp)
	{
	    // Connect the signals
	    subtractor = new N_FullSubtractor("subtractor");

            subtractor->clk(clk);
            subtractor->reset(reset);

	    for(i = 0; i< n_bit; i++){
		    subtractor->a[i](a[i]);
            	    subtractor->b[i](b[i]);
            	    subtractor->difference[i](difference[i]);
	    }

	    subtractor->c_in(c_in);
	    subtractor->borrow_out(borrow_out);

	    

	    SC_THREAD(stimulus);
    }

    ~FS_TEST(){
	    sc_close_vcd_trace_file(pTracefile);	    
    }
};


void FS_TEST::stimulus(){

	
	//wait(tp/2);
	srand(time(NULL));
	while (true){
		cout << "start" <<endl;
		reset.write(rand() % 2);
		for(int i = 0; i<n_bit;i++){
			a[i] = rand() % 2;
		        b[i] = rand() % 2;
		}
		c_in = rand() % 2;
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

		cout << "difference = ";
		for(int i = n_bit-1; i>=0 ; i--){
			cout << difference[i];
		}
		cout << " ";

		cout << " borrow_out = " << borrow_out.read() << endl;
		cout << " reset = " << reset.read() << endl;
		cout << "end " << endl;
		


		//////////////////////////////////////////  adding singals to waveform ////////////////////////////////////////////////
                sc_bv<n_bit> a0, b0, diff0;

	        pTracefile = sc_create_vcd_trace_file("fs_waveforms");
	        for(int i = 0; i< n_bit; i++){
			a0[i] = a[i].read().get_bit(0);   ///// gets the 0th bit of ith index of a
		        b0[i] = b[i].read().get_bit(0);
		        diff0[i] = difference[i].read().get_bit(0);
	        }

                sc_trace(pTracefile, clk, "clk");
                sc_trace(pTracefile, reset, "reset");
	        sc_trace(pTracefile, a0, "trace_a");
	        sc_trace(pTracefile, b0, "trace_b");
	        sc_trace(pTracefile, diff0, "trace_diff0");
                sc_trace(pTracefile, c_in, "c_in");
                sc_trace(pTracefile, borrow_out, "borrow_out");
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		wait(tp);
	}
}


int sc_main(int argc, char* argv[]){
       FS_TEST test("test");
       sc_start(15*tp);
       sc_stop();
       return 0;
} 

