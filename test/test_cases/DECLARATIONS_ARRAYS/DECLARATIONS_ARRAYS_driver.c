#include <stdio.h>

char f();

int main(){
    printf("expected 35, got %d\n",f());
    if (f()==35) return 0;
    return 1;
}