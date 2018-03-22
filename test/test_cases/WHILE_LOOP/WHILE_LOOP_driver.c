int f(int x);

int main(){
    if (f(5)==0) {
        if(f(0)==0){
            return 0;
        }
        return 1;
    }
    return 2;
}