int x = 0;

int f() {
    x++;
    if(x < 3){
        f();
    }
    return x;
}