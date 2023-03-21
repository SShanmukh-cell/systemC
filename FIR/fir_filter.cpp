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

		//if(rst) outp.write(0);
		//else {
		//outp.write(0);
		//wait();

		/*while(1){
			for( i = 5-1; i >0; i--){
				block[i] = block[i-1];
			}
			block[0] = inp.read();
			cout << "block[" << i <<"] = " << block[i] << endl;

			for( i = 0; i<5; i++){
				temp += coef[i] * block[i];
				cout << "temp = " << temp << ", coef[" << i <<"] = " << coef[i] << ", block[" << i <<"] = " << block[i] << endl;
				//wait();
			}

			outp.write(temp);
			wait();
		}*/


			for(i = 0; i < 5; i++){
				if(i == 0) {
					block[i] = inp.read();
				}
				else {
					block[i] = block[i-1];
				}
				
				cout << "block[" << i <<"] = " << block[i] << endl;
				//wait();
			}
		        for(i =0; i<5; i++){	
				temp += coef[i] * block[i];
				cout << "temp = " << temp << ", coef[" << i <<"] = " << coef[i] << ", block[" << i <<"] = " << block[i] << endl;
				//wait();
			}

			outp.write(temp);
		//}	
	}

	SC_CTOR(fir_filter){
		//SC_CTHREAD(fir_filter_func, clk.pos());
		SC_METHOD(fir_filter_func);
		sensitive << clk.pos();
		//sensitive << rst.pos();
		//reset_signal_is("rst", true);
	}
};
