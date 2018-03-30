int f(int i, int j) {
    for(i = 0; i < 5; i = i+1){
        j = i + j;
    }
    return j;
}

int g(int i, int j) {
    for(; i < 5; i = i+1){
        j = i + j;
    }
    return j;
}

int h(int i, int j) {
    for(; i < 5;){
        j = i + j;
        i = i+1;
    }
    return j;
}