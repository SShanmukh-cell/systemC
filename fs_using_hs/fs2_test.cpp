//#include "fs.cpp"
#include "fs_nbit.cpp"


SC_MODULE(FS_TEST){

    sc_clock clk;
    sc_signal<bool> reset;
    sc_signal<sc_bv<1>> a[n_bit], b[n_bit], difference[n_bit], c_in;
    sc_signal<sc_bv<1>> borrow_out;

    // Instantiate the N-bit subtractor
    //sc_trace_file *pTracefile;

    N_FullSubtractor* subtractor;


    void stimulus();


    SC_CTOR(FS_TEST):
	    clk("clk", tp)
	{
	    // Connect the signals
	    subtractor = new N_FullSubtractor("subtractor");

            subtractor->clk(clk);
            subtractor->reset(reset);

	    for(int i = 0; i< n_bit; i++){
		    subtractor->a[i](a[i]);
            	    subtractor->b[i](b[i]);
            	    subtractor->difference[i](difference[i]);
	    }

	    subtractor->c_in(c_in);
	    subtractor->borrow_out(borrow_out);

	   

            //Open VCD file
           /*pTracefile = sc_create_vcd_trace_file("waveforms");
	    
            sc_trace(pTracefile, clk, "clk");
            sc_trace(pTracefile, reset, "reset");
	    for(int i = 0; i< n_bit; i++){
                sc_trace(pTracefile, a[i], "a"+ std::to_string(i));
                sc_trace(pTracefile, b[i], "b"+ std::to_string(i));
                sc_trace(pTracefile, difference[i], "difference"+ std::to_string(i));
	    }
            sc_trace(pTracefile, c_in, "c_in");
            sc_trace(pTracefile, borrow_out, "borrow_out");*/

	    SC_THREAD(stimulus);
    }

    ~FS_TEST(){
	    //sc_close_vcd_trace_file(pTracefile);
	    /*for(i = 0; i<n_bit; i++){
			delete FS[i];
		}*/
	    //delete subtractor;
	    
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
		
		//cout << "a = " << a[i].read() << " b = " << b[i].read() << " difference = " << difference[i].read() << " borrow_out = " << borrow_out.read() << endl;
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
		//c_in.write(rand() % (1<<n_bit));
		//cout << "a = " << a.read() << " b = " << b.read() << " difference = " << difference.read() << " borrow_out = " << borrow_out.read() << endl;
		//cout << "a = " << a.read() << " b = " << b.read() << " c_in = " << c_in.read() << " difference = " << difference.read() << " borrow_out = " << borrow_out.read() << endl;
		wait(tp);
	}
}


int sc_main(int argc, char* argv[]){
       FS_TEST test("test");
       sc_start(15*tp);
       sc_stop();
       return 0;
} 

