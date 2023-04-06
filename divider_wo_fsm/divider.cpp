#include <systemc.h>
#include "const.h"


SC_MODULE(divider_N) {                            ///  code is flexible in N bit input which can be changed from const.h
	sc_in<sc_bv<N>> dividend;
	sc_in<sc_bv<N>> divisor;
	sc_out<sc_bv<N>> quotient;
	sc_out<sc_bv<N>> remainder;
	sc_in<bool> clk, rst;

	int i, j;
	

	void divider_func(){
		sc_bv<N> D, d, temp_d, q, r;
		sc_uint<N> incr, temp_q;
		D = dividend.read();
		d = divisor.read();
		temp_d = divisor.read();	
	
		incr = 0;
		temp_q = 0;
		
	        if(sc_uint<N>(d) == 1) {
			q = D;
			r = 0;
		}
		else if(sc_uint<N>(d) == sc_uint<N>(D)) {
        		q = 1;
        		r = 0;
		}
		else if(sc_uint<N>(d) > sc_uint<N>(D)){
			q = 0;
			r = D;
		}
		else if(sc_uint<N>(d) == 0) {
			cerr << "divisor must be greater that 0! " << endl;
			cerr << "Enter valid divisor" << endl;
		}
		else {       
       			for(i = 0; i < sc_uint<N>(D); i++){                        //// this for: i can left shift divisor and get close to the actuall divisor(so that i cont multiply and check for all possible divisor starting from 0
          			if(sc_uint<N+N>(temp_d << 1) < sc_uint<N>(D)) {
            				temp_d = temp_d << 1; 					
            				incr = sc_uint<N>(incr) + 1;					
          			}
          			else {
            				break;
          			}
        		}			
        		temp_q = 1 << incr;			                  /////  this for: i will start from last max left shift for which my divisor is less than dividend and from there i will start my multiplication by incrementing by 1
        		for(j = 0; j < sc_uint<N>(D); j++){				
          			if((sc_uint<N+N>(d) * temp_q) < sc_uint<N>(D)) {
            				temp_d = sc_uint<N>(d) * temp_q; 					
            				temp_q = sc_uint<N>(temp_q) + 1;					
          			}
          			else {
            				break;
          			}
        		}			
        		q = sc_uint<N>(temp_q) - 1;			
        		r = sc_uint<N>(D) - sc_uint<N>(temp_d);        
      		}
		quotient.write(q);
		remainder.write(r);

	}

	SC_CTOR(divider_N):
		dividend("div_dividend"),
		divisor("div_divisor"),
		quotient("div_quotient"),
		remainder("div_remainder"),
		rst("div_rst"),
		clk("div_clk")
	{		
		SC_METHOD(divider_func);
		sensitive << clk.pos();
		sensitive << dividend << divisor;		
	}
};
