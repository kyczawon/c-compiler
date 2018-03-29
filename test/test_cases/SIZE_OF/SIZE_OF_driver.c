#include <stdio.h>
int f(int x, short y, char z);

int main(){
    int x = f(5, 6, 7);
    printf("expected 14 got %d\n",x);
    if (x==14) {
        return 0;
    }
    return 1;
}