//#include <systemc.h>
#include "fa_nbit.cpp"

//#include "systemc.h"

int sc_main(int argc, char* argv[]) {
    sc_signal<sc_bv<1>> a[16];
    sc_signal<sc_bv<1>> b[16];
    sc_signal<sc_bv<1>> c_in;
    sc_signal<sc_bv<1>> sum[16];
    sc_signal<sc_bv<1>> c_out;
    sc_signal<bool> clk, reset;

    // Initialize inputs
    srand(time(NULL));
    for (int i = 0; i < 16; i++) {
        a[i] = rand() % 2;
        b[i] = rand() % 2;
    }
    c_in = rand() % 2;

    // Instantiate FullAdder16 module
    N_FullAdder fulladder("fulladder");
    for (int i = 0; i < 16; i++) {
        fulladder.a[i](a[i]);
        fulladder.b[i](b[i]);
        fulladder.sum[i](sum[i]);
    }
    fulladder.c_in(c_in);
    fulladder.c_out(c_out);
    fulladder.clk(clk);
    fulladder.reset(reset);

    // Simulate for 10 ns
    sc_start(tp);

    // Change inputs and continue simulating for another 10 ns
    //c_in = 1;
    //sc_start(10, SC_NS);

    // Print out results
    std::cout << "Inputs: a = ";
    for (int i = 15; i >= 0; i--) {
        std::cout << a[i];
    }
    std::cout << ", b = ";
    for (int i = 15; i >= 0; i--) {
        std::cout << b[i];
    }
    std::cout << ", c_in = " << c_in << std::endl;
    std::cout << "Outputs: sum = ";
    for (int i = 15; i >= 0; i--) {
        std::cout << sum[i];
    }
    std::cout << ", c_out = " << c_out << std::endl;

    return 0;
}
