int f() {
    int j = 0;
    for(int i = 0; i < 5; i++){
        j = i + j;
    }
    return j;
}