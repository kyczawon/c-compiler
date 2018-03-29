#include <stdio.h>

short f(short x, short y);

int main(){
    printf("expected 1964, got %d\n",f(64000,2500));
    if (f(64000,2500) == 1964) return 0;
    return 1;
}