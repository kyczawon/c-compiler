#include <stdio.h>
int f(int x);

int main(){
    int x = f(5);
    printf("expected 5 got %d\n",x);
    if (x==5) {
        return 0;
    }
    return 1;
}