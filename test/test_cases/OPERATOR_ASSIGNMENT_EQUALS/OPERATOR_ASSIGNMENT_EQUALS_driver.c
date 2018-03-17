#include <stdio.h>
int f(int x, int y);

int main(){
    int x = f(8,4);
    if (x==4) {
        printf("x=4 passed got %d\n",x);
        int y = f(10,-4);
        if (y==-4) {
            printf("y=-4 passed got %d\n",y);
            return 0;
        }
        else printf("y=-4 failed, got %d\n",y);
    } else printf("x=4 failed, got %d\n",x);
    return 1;
}