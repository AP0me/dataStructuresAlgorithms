#include<stdio.h>
#include<stdlib.h>

double plus(double x, double y) {return x+y;}
double minus(double x, double y) {return x-y;}
double mult(double x, double y) {return x*y;}
double Div(double x, double y) {return x/y;}
double Mod(double x, double y) {return (int)x%(int)y;}
double error(double x, double y) {
fprintf(stderr,"ERROR! The only valid operators are + - * / %%\n");
return 0;
}

//Array of pointers on functions
double (*f[])()={plus, minus, mult, Div, Mod, error};

int main(){
double d=0;
char szString[100], *p;
double td[10];
int i=0;

int aF[256]; // array of functions
for (int i=0;i<256;aF[i++]=5);
aF['+']=0; aF['-']=1; aF['*']=2; aF['x']=2; aF['/']=3; aF['%']=4;

}