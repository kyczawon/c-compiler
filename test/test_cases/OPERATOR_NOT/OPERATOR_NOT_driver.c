#include <stdio.h>
int f(int x);

int main(){
    int x = f(1);
    if (!x) {
        printf("!1 passed got %d\n",x);
        int y = f(0);
        if (y) {
            printf("!0 passed got %d\n",y);
            return 0;
        }
        else printf("!0 failed, got %d\n",y);
    } else printf("!1 failed, got %d\n",x);
    return 1;
}