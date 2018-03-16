#include <stdio.h>
int f(int x, int y);

int main(){
    int x = f(3,4);
    if (x==7) {
        printf("3+4 passed got %d\n",x);
        int y = f(4,-3);
        if (y==1) {
            printf("4+(-3) passed got %d\n",y);
            return 0;
        }
        else printf("4+(-3) failed, got %d\n",y);
    } else printf("3+4 failed, got %d\n",x);
    return 1;
}