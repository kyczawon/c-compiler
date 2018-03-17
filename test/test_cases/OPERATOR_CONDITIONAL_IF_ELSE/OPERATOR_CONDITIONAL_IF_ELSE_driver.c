#include <stdio.h>
int f(int x, int y);

int main(){
    int x = f(8,4);
    if (x==5) {
        printf("(8==4) ? 3 : 5 passed, got %d\n",x);
        int y = f(4,4);
        if (y==3) {
            printf("(4==4) ? 3 : 5 passed, got %d\n",y);
            return 0;
        }
        else printf("(8==4) ? 3 : 5 failed, got %d\n",y);
    } else printf("(3==4) ? 3 : 5 failed, got %d\n",x);
    return 1;
}