int z;
int *x;
int *y = &z;

void f() {
    *x=*x-1;
}