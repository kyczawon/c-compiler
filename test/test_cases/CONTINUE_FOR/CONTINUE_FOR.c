int f() {
    int j = 0;
    int i;
    for(i = 0; i < 5; i = i+1){
        if(i==2) continue;
        j = i + j;
    }
    return j;
}