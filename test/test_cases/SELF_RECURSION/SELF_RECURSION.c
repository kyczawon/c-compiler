int x;

int f() {
    x++;
    if(x < 3){
        f();
    }
    return x;
}