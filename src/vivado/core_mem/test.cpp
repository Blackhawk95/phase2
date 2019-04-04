#include <iostream>
#include <ap_int.h>


typedef /*long long int*/ ap_int<16> addr_uint;
typedef ap_int<8> int8;

addr_uint a = 1900;
int8 ma = 54;
int8 flag = 0x02;
int8 data = 15;

void mem(addr_uint,int8,int8*,int8);

int main(){

mem(a,ma,&data,flag);
data = 10;
std::cout<<data<<"\n";
flag = 0x03;
mem(a,ma,&data,flag);
std::cout<<data<<"\n";
return 0;
}
