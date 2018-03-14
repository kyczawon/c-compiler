#include <stdlib.h>

double f(char* x);

int main(){
    int y = f("11.25") - 11.25;
    if (!y)
        return 0;
    return 1;
    

}