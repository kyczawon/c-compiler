int f(int x) {
    int *z;
    z = &x;
    *z = 5;
    return x;
}