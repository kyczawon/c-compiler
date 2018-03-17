#include <stdio.h>
int f(int x, int y, int z);

int main(){
    int x = f(3,4,3);
    if (x==7) {
        printf("x = --3; y=4--; --x+y+3-- passed got %d\n",x);
        return 0;
    } else printf("x = --3; y=4--; --x+y+3-- failed got %d\n",x);
    return 1;
}