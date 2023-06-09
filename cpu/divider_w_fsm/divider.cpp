#include <systemc.h>
#include "const.h"
#include "mul.cpp"
#include "sub.cpp"
#include "add.cpp"
#include "right_shift.cpp"
#include "greater_equal.cpp"



SC_MODULE(divider_N) {                            ///  code is flexible in N bit input which can be changed from const.h
	sc_in<sc_biguint<N>> dividend;
	sc_in<sc_biguint<N>> divisor;
	sc_out<sc_biguint<N>> Q;
	sc_out<sc_biguint<N>> R;
	sc_in<bool> clk, rst;
	sc_in<sc_biguint<1>> req;
	sc_out<sc_biguint<1>> ready, exception;

	int i, j, k;	

	sc_signal<sc_biguint<N>> D, d, Counter, RefCounter, refD, refd, Num_cycles;
        sc_signal<sc_biguint<N>> Dr, temp1, temp2, temp3;

	sc_signal<sc_biguint<1>> g, e;
	
	typedef enum {START, COMPARE} state;
	state s;


	void divider_func(){
		if(rst){
			s = START;
			RefCounter = 0;
			Counter = 0;
      			exception = 0;
      			ready = 0;
      			Num_cycles = 0;
		}
		else {
			if(s == START){
				if(req==1){
					if(divisor == 0){
						exception = 1;
				     		ready = 1;
            					s = START;  
            					Num_cycles = 1;
          				} 
					else if(divisor == 1) {
            					exception = 0;
            					ready = 1;
            					s = START;
            					Q.write(dividend.read());
            					Num_cycles = 1;
          				} 
					else {
						s = COMPARE;            					
            					refD = dividend.read();
            					refd = divisor.read();
            					D = dividend.read();
            					d = divisor.read();
            					Num_cycles = 1;
					}
				} 
				else {
          				s = START;
          				ready = 0;
          				Num_cycles = 0;
        			}
     			} 
			else if(s == COMPARE) {
				Num_cycles = Num_cycles + 1;
        			if((e==1) || (g==1)){          				
          				D = Dr;          			
					if(Counter == 0) {
						Counter = 1;
					}
					else{
						Counter = Counter << 1;
					}
        			}
				else {          				          
          				if(Counter != 0) {            					
            					RefCounter = temp3;
            					Counter = 0;            					
            					D = temp2;
            					refD = temp2;        
          				} 
          				else {             					
             					Q.write(RefCounter);
             					ready = 1;
             					s = START;
          				}
        			}
      			}
		}
	}



	SC_CTOR(divider_N):
		dividend("div_dividend"),
		divisor("div_divisor"),
		Q("div_Q"),
		R("div_R"),
		req("div_req"),
		ready("div_ready"),
		exception("div_exception"),
		rst("div_rst"),
		clk("div_clk")
	{	
		SC_METHOD(divider_func);
		sensitive << clk.pos();
		sensitive << rst.pos(); 
		
		
		greater_equal* ge_i;                            
		ge_i = new greater_equal("ge_i");
		ge_i->A(D);
		ge_i->B(d);             
		ge_i->G(g);
		ge_i->E(e);

		
		/*SC_METHOD(divider_func);
		sensitive << clk.pos();
		sensitive << rst.pos();*/
		
		
		mul* mul_i;                            
		mul_i = new mul("mul_i");
		mul_i->A(refd);
		mul_i->B(Counter);             
		mul_i->O(temp1);		 
		

		sub* sub_i;                            
		sub_i = new sub("sub_i");
		sub_i->A(refD);
		sub_i->B(temp1);             
		sub_i->O(temp2);


		add* add_i;                            
		add_i = new add("add_i");
		add_i->A(RefCounter);
		add_i->B(Counter);             
		add_i->O(temp3);


		right_shift* rshift_i;                            
		rshift_i = new right_shift("rshift_i");
		rshift_i->inp(D);
		rshift_i->out(Dr);

		/*SC_METHOD(divider_func);
		sensitive << clk.pos();
		sensitive << rst.pos();*/
	}
};
