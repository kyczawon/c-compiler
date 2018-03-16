#include <stdlib.h>

double f();

int main(){
    int y = f() - 11.25;
    if (!y)
        return 0;
    return 1;
    

}