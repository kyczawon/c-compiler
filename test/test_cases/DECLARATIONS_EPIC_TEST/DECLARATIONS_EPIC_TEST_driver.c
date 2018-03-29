#include <stdio.h>

char f();

int main(){
    printf("expected 11, got %d\n",f());
    if (f()) return 0;
    return 1;
}