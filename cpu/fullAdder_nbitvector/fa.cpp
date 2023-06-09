#include "ha.cpp"

// Full Adder module
SC_MODULE(FullAdder) {
    sc_in<sc_biguint<1>> a, b, c_in;
    sc_out<sc_biguint<1>> c_out;
    sc_out<sc_biguint<1>> sum;
    sc_in<bool> clk, reset;

    sc_signal<sc_biguint<1>> sum_i;
    sc_signal<sc_biguint<1>> carry_0, carry_1;

    HalfAdder* ha1;
    HalfAdder* ha2;

    void full_adder_process() {	   
	   if(reset) c_out.write(0);
	   else c_out.write(carry_1.read() | carry_0.read());
    }

    SC_CTOR(FullAdder):
	    a("fa_a"),
	    b("fa_b"),
	    c_in("fa_cin"),
	    sum("fa_sum"),
	    c_out("fa_c_out"),
	    clk("fa_clk"),
	    reset("fa_reset")
    {

	    ha1 = new HalfAdder("ha1");
            ha2 = new HalfAdder("ha2");
	
	    ha1->a(a);
            ha1->b(b);
            ha1->sum(sum_i);
            ha1->carry(carry_0);
	    ha1->clk(clk);
	    ha1->reset(reset);

            ha2->a(sum_i);
            ha2->b(c_in);
            ha2->sum(sum);
            ha2->carry(carry_1);
	    ha2->clk(clk);
	    ha2->reset(reset);


            SC_METHOD(full_adder_process);
            sensitive << carry_0 << carry_1;
    }
};
