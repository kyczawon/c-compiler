int f(int x) {
    int test[4];
    test[3] = x;
    return test[3];
}

int g() {
    int test[4] = {10,20,2};
    return test[2];
}

int h() {
    int test[4] = {10,20,2};
    return test[0] + test[1];
}