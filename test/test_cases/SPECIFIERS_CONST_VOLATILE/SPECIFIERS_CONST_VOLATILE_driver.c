#include <stdio.h>

char f(unsigned int x);

int main(){
    printf("expected 15, got %d\n",f(5));
    if (f(5) == 15) return 0;
    return 1;
}