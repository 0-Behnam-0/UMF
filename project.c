#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

void parser(char user_input [0]){
    printf("command: %s", user_input);
}

void main()
{
    char user_input[30];
    fgets(user_input, sizeof(user_input), stdin);
    printf("%s", user_input);
    parser(user_input);
    // char* command = "ls";
    // char* args[] = {"ls", NULL};
    // execvp(command, args);
}
