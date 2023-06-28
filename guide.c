#include <stdio.h>

// for booleans
#include <stdbool.h>

// for strings
#include <string.h>

int main(){
    printf("hello mate\n");
    int MyVar;
    MyVar = 10;

    // change data type
    float mv = (float) MyVar;

    // constant
    const char read_only_var[] = "Read Only";
    printf("this is MyVar: %.1f - %s\n", mv, read_only_var);

    // user input
    char MyInputS[30];
    char MyInputF[30];
    printf("Type a number: ");
    // scanf("%s", &MyInputS);                          // for one word
    // printf("%s", MyInputS);
    fgets(MyInputF, sizeof(MyInputF), stdin);         // for two or more words
    printf("%s", MyInputF);
    

    // seprating output and bullshits, remove it in product mode
    printf("\n\n--------------------------\n");
    
    return 0;
}
