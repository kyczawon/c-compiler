#include <stdio.h>
int f(int x, int y);

int main(){
    int x = f(12,8);
    if (x==0) {
        printf("12>>8 passed: expected 0 got %d\n",x);
        int y = f(1923,3);
        if (y==240) {
            printf("1923>>3 passed: expected 240 got %d\n",y);
            return 0;
        }
        else printf("12>>8 failed: expected 0 got %d\n",y);
    } else printf("923>>3 failed: expected 240 got %d\n\n",x);
    return 1;
}