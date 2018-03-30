int f(int x) {
    if(x <= 1){
        return 1;
    } else {
        return x*f(x-1);
    }
}

int g(int y){
    ++y;
    if(y<3){
        return g(y);
    }
    return y;
}