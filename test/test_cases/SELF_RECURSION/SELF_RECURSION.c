int f(int* x) {
    (*x)++;
    if(*x < 3){
        f(x);
        // printf("recursion");
    }
    return *x;
}