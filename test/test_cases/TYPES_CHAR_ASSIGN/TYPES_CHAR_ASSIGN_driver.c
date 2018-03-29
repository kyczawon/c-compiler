#include <stdio.h>

char f();

int main(){
    printf("expected -107, got %d\n",f());
    if (f() == -107) return 0;
    return 1;
}