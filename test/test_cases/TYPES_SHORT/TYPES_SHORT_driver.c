#include <stdio.h>

short f(short x, short y);

int main(){
    printf("expected -4036, got %d\n",f(58000,2500));
    if (f(58000,2500) == -4036) return 0;
    return 1;
}