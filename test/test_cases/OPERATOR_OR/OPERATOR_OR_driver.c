#include <stdio.h>
int f(int x, int y);

int main(){
    int x = f(1,0);
    if (x) {
        printf("1||0 passed, got %d\n",x);
        int y = f(0,1);
        if (y) {
            printf("0||1 passed, got %d\n",y);
            int z = f(1,1);
            if (z) {
                printf("1||1 passed, got %d\n",z);
                int w = f(0,0);
                if (!w) {
                    printf("0||0 passed, got %d\n",y);
                    return 0;
                } else printf("0||0 failed, got %d\n",y);
            } else printf("1||1 failed, got %d\n",y);
        } else printf("0||1 failed, got %d\n",y);
    } else printf("1||0 failed, got %d\n",x);
    return 1;
}