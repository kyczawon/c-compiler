#include <stdio.h>
void evaluateTest(char* info, int expect, int result, int* total, int* passed);
int f(int x);
int g();
int h();
int i();
int j();

int main(){
    int total = 0;
    int passed = 0;
    evaluateTest("Array declaration, seperate assingment and array operator", 5, f(5), &total, &passed);
    evaluateTest("Array declaration inline assingment and array operator", 2, g(), &total, &passed);
    evaluateTest("Array declaration inline expression assingment and array operator addition",30, h(), &total, &passed);
    printf("Passed %d/%d tests\n",passed,total);
    if (total == passed) return 0;
    return 1;
}

void evaluateTest(char* info, int expect, int result, int* total, int* passed) {
    char* pass = "";
    (*total)++;
    if (result == expect) {
        pass = "PASSED";
        (*passed)++;
    } else pass = "FAILED";
    printf("%s %s, expected %d, got %d\n",info,pass,expect,result);
}