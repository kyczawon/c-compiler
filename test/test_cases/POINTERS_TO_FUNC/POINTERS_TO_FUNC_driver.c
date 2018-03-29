#include <stdio.h>

int f(int* x, int* y);

int main(){
    int y = 10;
    int z = 100;
    f(&y, &z);
    printf("expected 5 got %d\n",y);
    printf("expected 10 got %d\n",z);
    if (y == 5 && z == 10)
        return 0;
    return 1;
}