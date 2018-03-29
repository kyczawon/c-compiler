int f() {
    int x=5,*y=&x, *z, i;
    x = 6;
    z = &x;
    i = 4;
    return x+*z+*y+i;
}