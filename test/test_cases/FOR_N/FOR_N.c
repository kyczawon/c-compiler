int f() {
    int j = 0;
    for(int i = 0; i < 5; i = i+1){
        j = i + j;
    }
    return j;
}