int x;

int f();

int main(){
    x = 5;
    f();
    if (x == 4){
        x = 12;
        f();
        if(x==11) 
            return 0;
        return 1;
    }
    return 1;
    

}