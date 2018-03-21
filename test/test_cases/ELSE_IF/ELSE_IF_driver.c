int f(int x, int y);

int main(){

    if (f(1,1)==1) {  
        if (f(2,5)==89){
            if(f(1,3)==3){
                if(f(9,4)==4){
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