#include <stdio.h>
int f(int x, int y);

int main(){
    int x = f(12312,10293);
    if (x==14397) {
        printf("12312|10293 passed: expected 14397 got %d\n",x);
        int y = f(14207,15803);
        if (y==16383) {
            printf("14207|15803 passed: expected 16383 got %d\n",y);
            return 0;
        }
        else printf("14207|15803 failed: expected 16383 got %d\n",y);
    } else printf("12312|10293 failed: expected 14397 got %d\n",x);
    return 1;
}