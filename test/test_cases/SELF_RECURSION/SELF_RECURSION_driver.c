int f(int* x);

int main(){
    int x = 0;
    if (f(&x) == 3)
        return 0;
    return 1;
    

}