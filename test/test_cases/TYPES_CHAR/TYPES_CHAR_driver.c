#include <stdio.h>

char f(char x, char y);

int main(){
    printf("expected -100, got %d\n",f(97,49));
    if (f(97,49) == -100) return 0;
    return 1;
}