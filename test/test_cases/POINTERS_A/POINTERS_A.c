int f(int x) {
    int *z = &x;
    *z = 5;
    return *z;
}