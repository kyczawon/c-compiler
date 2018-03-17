#include <stdio.h>
int f(int x, int y);

int main(){
    int x = f(8,4);
    if (!x) {
        printf("8<=4 passed got %d\n",x);
        int y = f(1,4);
        if (y) {
            printf("1<=4 passed got %d\n",y);
            int z = f(1,1);
            if (z) {
                printf("1<=1 passed got %d\n",z);
                return 0;
            } else printf("1<=1 failed, got %d\n",z);
        } else printf("1<=4 failed, got %d\n",y);
    } else printf("8<=4 failed, got %d\n",x);
    return 1;
}