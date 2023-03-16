#include <systemc.h>

int sc_main(int agrv,char* argc[]){
       char a[] = "Hello world";
       char b[5];

       //initialization
       b[0] = 'H';
       b[1] = 'e';
       b[2] = 'l';
       b[3] = 'l';
       b[4] = 'o';
  
       //below initializations types are not allowed
       //b = "Hello";
       //b = {'H','e','l','l','o'};
  
       cout <<"Value of a = "<< a <<endl;
       cout <<"Value of b = "<< b <<endl;
       return 0;
}       
