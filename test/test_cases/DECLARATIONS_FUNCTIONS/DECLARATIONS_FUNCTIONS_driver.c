#include <stdio.h>

int main(){
    printf("expected 10, got %d\n",f(10));
    if (f(10) == 10) return 0;
    return 1;
}