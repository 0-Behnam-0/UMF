#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    char command[100]; // Buffer to hold the user input command
    printf("Enter a command: ");
    fgets(command, sizeof(command), stdin); // User input

    command[strcspn(command, "\n")] = '\0'; // Remove newline character from the command

    char *token;            // Split the command into tokens based on spaces
    const int arg_max = 20; // Set maximum arg size which is readable only
    char *args[arg_max];    // Maximum arguments excluding the command itself

    int i = 0;
    token = strtok(command, " "); // First element of command parsed into token
    while (token != NULL && i < arg_max + 1)
    {
        args[i++] = token;
        token = strtok(NULL, " ");
    }

    args[i] = NULL; // Set the last element to NULL
    /*
    Warning: Ignoring this line of code cause the pointer moves into inaccessible memory address,
     and finally 'Bad address' error will be rised!
    */

    printf("args = "); // printing the user's input
    for (int j = 0; j < i; j++)
    {
        printf("%s ", args[j]);
    }
    printf("\n");

    execvp(args[0], args); // Execute the command

    perror("execvp"); // Print an error message if execvp fails

    return 0;
}
