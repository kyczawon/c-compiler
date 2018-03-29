#include <stdio.h>

int f();

int main(){
    printf("expected 2, got %d\n",f());
    if (f()==22) return 0;
    return 1;
}