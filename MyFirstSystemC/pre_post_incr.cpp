#include <systemc.h>

int sc_main (int argc, char* argv[]) {
  int a = 5;

  //pre-increment
  cout <<"Pre Increment Value of a with value 5 = " << ++a << endl;   /// here the value will first be incremented, and the new value will be printed
  
  int b = 5;

  //post-increment
  cout <<"Post Increment Value of b with value 5 = " << b++ << endl;   //  here the old value will first get printed and than incremented value stores in the operand

  int x = 5;
  int y = 0;

  y = ++x; // pre-increment, x is now 6, y is assigned the value 6
  cout <<"Pre Increment value of y is " << y << endl;
  cout <<"Pre Increment Value of X is " << x << endl;
  y = x++; // post-increment, x is now 7, y is assigned the value 6 (the previous value of x)
  cout <<"Post Increment value of y is " << y << endl;
  cout <<"Post Increment Value of X is " << x << endl;  
  return 0;// Terminate simulation  
}
