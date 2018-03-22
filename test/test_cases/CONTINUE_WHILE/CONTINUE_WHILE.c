int f() {

    int a = 0;
    int j = 0;
    while( a < 10 ){
   
        if( a == 5) {
            a = a + 1;
            continue;
            return 1;
        }
        a = a+1;
        j = j + a;
   
    }
 
    return j;
}