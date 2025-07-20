#include "Power.hpp"

long double power(double a ,int b){
    for(int i = 0; i < b; i++) a *=a;
    return (b>0)?a:1;
}