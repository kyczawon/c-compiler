#include <stdio.h>
int f(int x, int y);

int main(){
    int x = f(8,4);
    if (x==2) {
        printf("8/4 passed got %d\n",x);
        int y = f(10,4);
        if (y==2) {
            printf("10/4 passed got %d\n",y);
            return 0;
        } else printf("10/4 failed, got %d\n",y);
    } else printf("8/4 failed, got %d\n",x);
    return 1;
}