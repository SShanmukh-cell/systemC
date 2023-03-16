#include "counter.cpp"

void counter::func_counter(){
	if(clr) incr = 0;
	else incr++;

	count = incr;
}
