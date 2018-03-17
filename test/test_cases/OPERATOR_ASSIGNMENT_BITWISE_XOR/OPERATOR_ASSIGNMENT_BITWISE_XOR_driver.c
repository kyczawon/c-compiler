#include <stdio.h>
int f(int x, int y);

int main(){
    int x = f(12312,10293);
    if (x==6189) {
        printf("12312^=10293 passed: expected 6189 got %d\n",x);
        int y = f(14207,15803);
        if (y==2756) {
            printf("14207^=15803 passed: expected 2756 got %d\n",y);
            return 0;
        }
        else printf("14207^=15803 failed: expected 2756 got %d\n",y);
    } else printf("12312^=10293 failed: expected 6189 got %d\n\n",x);
    return 1;
}