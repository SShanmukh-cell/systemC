#include "add.cpp"


SC_MODULE(divider_N) {                            ///  code is flexible in N bit input which can be changed from const.h
	sc_in<sc_bv<N>> dividend;
	sc_in<sc_bv<N>> divisor;
	sc_out<sc_bv<N>> Q;
	sc_out<sc_bv<N>> R;
	sc_in<bool> clk, rst;
	sc_in<sc_bv<1>> req;
	sc_out<sc_bv<1>> ready, exception;

	int i, j, k;
	
	/*sc_signal<sc_bv<N>> mul_i_out[N];
	sc_signal<sc_bv<N+N+N>> temp_Q[N];
	sc_signal<sc_bv<N>> shift0[N];
	sc_signal<sc_bv<N>> valid1[N];*/

	sc_signal<sc_bv<N>> D, d, Counter, RefCounter, refD, refd, Num_cycles;
        sc_signal<sc_bv<N>> Dr, temp1, temp2, temp3;

	sc_signal<sc_bv<1>> g, e;
	
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
				if(sc_biguint<N>(req)==1){
					if(sc_biguint<N>(divisor) == 0){
						exception = 1;
				     		ready = 1;
            					s = START;  
            					Num_cycles = 1;
          				} 
					else if(sc_biguint<N>(divisor) == 1) {
            					exception = 1;
            					ready = 1;
            					s = START;
            					Q = dividend.read();
            					Num_cycles = 1;
          				} 
					else {
						s = COMPARE;
            					//Data
            					refD = dividend.read();
            					refd = divisor.read();
            					D = dividend.read();
            					d = divisor.read();
            					Num_cycles = 1;
					}
				} 
				else {
          				s = START;
          				ready = 1;
          				Num_cycles = 0;
        			}
     			} 
			else if(s == COMPARE) {
				Num_cycles = sc_biguint<N>(Num_cycles) + 1;
        			if((sc_biguint<N>(e)==1) || (sc_biguint<N>(g)==1)){
          				// divisor =< Divid}
          				D = Dr;
          				//Counter = (Counter == 0) ? 1 : Counter << 1;//Bug: Counter << 1;
					if(sc_biguint<N>(Counter) == 0) {
						Counter = 1;
					}
					else{
						Counter = sc_biguint<N>(Counter) << 1;
					}
        			}
				else {
          				// divisor > Divid}          
          				if(sc_biguint<N>(Counter) != 0) {
            					//RefCounter = RefCounter + Counter;
            					RefCounter = temp3;
            					Counter = 1;
            					//D = refD - refd*Counter;
            					D = temp2;
            					refD = temp2;        
          				} else { 
            					/// Sum of Counter values will be output.
             					Q = RefCounter;
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
		greater_equal* ge_i;                            
		ge_i = new greater_equal("ge_i");
		ge_i->A(D);
		ge_i->B(d);             
		ge_i->G(g);
		ge_i->E(e);

		
		SC_METHOD(divider_func);
		sensitive << clk.pos();
		sensitive << rst.pos();
		
		
		mul* mul_i;                            
		mul_i = new mul("mul_i");
		mul_i->A(refd);
		mul_i->B(Counter);             
		mul_i->O(temp1);		 
		

		add* add_i;                            
		add_i = new add("add_i");
		add_i->A(RefCounter);
		add_i->B(Counter);             
		add_i->O(temp3);


		sub* sub_i;                            
		sub_i = new sub("sub_i");
		sub_i->A(refD);
		sub_i->B(temp1);             
		sub_i->O(temp2);


		right_shift* rshift_i;                            
		rshift_i = new right_shift("rshift_i");
		rshift_i->inp(D);
		rshift_i->out(Dr);
	}
};
