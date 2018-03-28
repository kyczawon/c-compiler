int f(int x, int y) {
    int test[4];
    test[0] = x;
    test[1] = y;
    test[2] = x+y;
    test[3] = x+x;

    return test[0] + test[1] + test[2] + test[3];
}