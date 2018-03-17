#include <stdio.h>
int f(int x, int y);

int main(){
    int x = f(12312,10293);
    if (x==8208) {
        printf("12312&=10293 passed: expected 8208 got %d\n",x);
        int y = f(14207,15803);
        if (y==13627) {
            printf("14207&=15803 passed: expected 13627 got %d\n",y);
            return 0;
        }
        else printf("14207&=15803 failed: expected 13627 got %d\n",y);
    } else printf("12312&=10293 failed: expected 8208 got %d\n\n",x);
    return 1;
}