#include <stdio.h>

signed int f(unsigned int x);

int main(){
    printf("expected -900001, got %d\n",f(4294067295));
    if (f(4294067295) == -900001) return 0;
    return 1;
}