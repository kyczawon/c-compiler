int f(int x);

int main(){

    if(f(1)==1 ){
        if(f(2)==2){
            if(f(3)==3){
                if(f(4)==4){
                    return 0;
                }
                return 1;
            }
            return 1;
        }
        return 1;
    }
    return 1;

}