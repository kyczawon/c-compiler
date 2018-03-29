#include <stdio.h>

char f(char x, char y);

int main(){
    printf("expected -62, got %d\n",f(240,200));
    if (f(240,200) == -62) return 0;
    return 1;
}