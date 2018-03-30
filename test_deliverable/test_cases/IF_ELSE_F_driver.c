#include <stdio.h>
void evaluateTest(char* info, int expect, int result, int* total, int* passed);
int f(int x);

int main(){
    int total = 0;
    int passed = 0;
    evaluateTest("If else, if false", 5, f(5), &total, &passed);
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