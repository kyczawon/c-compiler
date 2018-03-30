#include <stdio.h>
void evaluateTest(char* info, int expect, int result, int* total, int* passed);
int f(int x, int y);
int g(int x, int y);
int h(int x, int y);

int main(){
    int total = 0;
    int passed = 0;
    evaluateTest("For loop", 11, f(0,1), &total, &passed);
    evaluateTest("For loop with no initialization", 11, g(0,1), &total, &passed);
    evaluateTest("For loop with no initialization and no increment", 11, h(0,1), &total, &passed);
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