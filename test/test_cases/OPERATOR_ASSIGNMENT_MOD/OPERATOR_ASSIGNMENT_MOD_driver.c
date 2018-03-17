#include <stdio.h>
int f(int x, int y);

int main(){
    int x = f(8,5);
    if (x==3) {
        printf("8%%=5 passed got %d\n",x);
        int y = f(-7,3);
        if (y==-1) {
            printf("-7%%=3 passed got %d\n",y);
            int z = f(7,-3);
            if (z==1) {
                printf("7%%=-3 passed got %d\n",z);
                return 0;
            } else printf("7%%=-3 failed, got %d\n",z);
        } else printf("-7%%=3 failed, got %d\n",y);
    } else printf("8%%=5 failed, got %d\n",x);
    return 1;
}