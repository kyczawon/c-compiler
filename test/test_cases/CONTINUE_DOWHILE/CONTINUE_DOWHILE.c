int f() {

    int a = 0;
    int j = 0;
    do {
   
        if( a == 5) {
            a = a + 1;
            continue;
            return 1;
        }
        a = a+1;
        j = j + a;
   
    } while( a < 10 );
 
    return j;
}