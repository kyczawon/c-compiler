#include <stdlib.h>

int f();

int main(){
    int y = f() - 11;
    if (!y)
        return 0;
    return 1;
    

}