#include <stdio.h>
int f(int x, int y);

int main(){
    int x = f(3,4);
    if (x) {
        printf("3!=4 passed got %d\n",x);
        int y = f(4,4);
        if (!y) {
            printf("4!=4 passed got %d\n",y);
            return 0;
        } else printf("4!=4 failed, got %d\n",y);
    } else printf("3!=4 failed, got %d\n",x);
    return 1;
}