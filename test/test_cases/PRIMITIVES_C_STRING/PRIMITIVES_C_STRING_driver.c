#include <stdio.h>
#include <string.h>
void evaluateTest(char* info, char* expect, char* result, int* total, int* passed);
char* f();


int main(){
    int total = 0;
    int passed = 0;
    evaluateTest("Decrementing global variable", "11", f(), &total, &passed);
    printf("Passed %d/%d tests\n",passed,total);
    if (total == passed) return 0;
    return 1;
}

void evaluateTest(char* info, char* expect, char* result, int* total, int* passed) {
    char* pass = "";
    (*total)++;
    if (strcmp(expect,result) == 0) {
        pass = "PASSED";
        (*passed)++;
    } else pass = "FAILED";
    printf("%s %s, expected %s, got %s\n",info,pass,expect,result);
}