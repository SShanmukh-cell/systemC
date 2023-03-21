#include <systemc.h>
#include "const.h"


SC_MODULE(fir_filter){

	sc_in<sc_uint<data_size>> inp;
	sc_out<sc_uint<data_size>> outp;
	sc_in<bool> clk, rst;

	void fir_filter_func(){

		sc_uint<data_size> block[coef_size];
		sc_uint<data_size> temp = 0;
		int i;

		if(rst) outp.write(0);
		else {
			for(i = 0; i < 5; i++){
				if(i == 0) {
					block[i] = inp.read();
				}
				else {
					block[i] = block[i-1];
				}
				
				
				temp += coef[i] * block[i];
				cout << "temp = " << temp << ", coef[" << i <<"] = " << coef[i] << ", block[" << i <<"] = " << block[i] << endl;
				cout << "current time step: " << sc_time_stamp() << endl;
			}

			outp.write(temp);
		}	
	}

	SC_CTOR(fir_filter){
		SC_METHOD(fir_filter_func);
		sensitive << clk.pos();
		//sensitive << rst.pos();
		//reset_signal_is("rst", true);
	}
};
