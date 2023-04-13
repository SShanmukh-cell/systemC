#include "systemc.h"
#include "const.h"


SC_MODULE(Rshift) {
    sc_in< sc_biguint<N> > i;
    sc_in<sc_biguint<S>> shift_by;
    sc_out< sc_biguint<N> > o;

    SC_CTOR(Rshift) {
        SC_METHOD(shift);
        sensitive << i << shift_by;
    }

    void shift() {
	    sc_uint<S> shift = shift_by.read();
	    o.write( (0, i.read().range(N-1, shift)));

    }
};

