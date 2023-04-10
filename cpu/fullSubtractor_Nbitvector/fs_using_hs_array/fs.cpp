#include "hs.cpp"

SC_MODULE(FullSubtractor) {
    sc_in<sc_bv<1>> a, b, c_in;
    sc_out<sc_bv<1>> borrow_out;
    sc_out<sc_bv<1>> difference;
    sc_in<bool> clk, reset;

    sc_signal<sc_bv<1>> difference_i;
    sc_signal<sc_bv<1>> borrow_0, borrow_1;

    HalfSubtractor* hs1;
    HalfSubtractor* hs2;

    void full_subtractor_process() {	    
	borrow_out.write(borrow_1.read() | borrow_0.read());
    }

    SC_CTOR(FullSubtractor){

	    hs1 = new HalfSubtractor("hs1");
            hs2 = new HalfSubtractor("hs2");
	
	    hs1->a(a);
            hs1->b(b);
            hs1->difference(difference_i);
            hs1->borrow(borrow_0);
	    hs1->clk(clk);
	    hs1->reset(reset);

            hs2->a(difference_i);
            hs2->b(c_in);
            hs2->difference(difference);
            hs2->borrow(borrow_1);
	    hs2->clk(clk);
	    hs2->reset(reset);
	
            SC_METHOD(full_subtractor_process);
            sensitive << borrow_0 << borrow_1;
    }
};
