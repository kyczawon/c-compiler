#include <stdio.h>

char f();

int main(){
    printf("expected -15, got %d\n",f());
    if (f()==-15) return 0;
    return 1;
}