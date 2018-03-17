#include <stdio.h>
int f(int x, int y);

int main(){
    int x = f(12,8);
    if (x==3072) {
        printf("12<<=8 passed: expected 3072 got %d\n",x);
        int y = f(1923,3);
        if (y==15384) {
            printf("1923<<=3 passed: expected 15384 got %d\n",y);
            return 0;
        }
        else printf("12<<=8 failed: expected 0 got %d\n",y);
    } else printf("923<<=3 failed: expected 15384 got %d\n\n",x);
    return 1;
}