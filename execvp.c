#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    char command[100]; // Buffer to hold the user input command
    do
    {
        printf("Enter a command: ");
        fgets(command, sizeof(command), stdin); // User input

        command[strcspn(command, "\n")] = '\0'; // Remove newline character from the command('\n' will replaced with '\0')

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

        printf("args = "); // Printing the user's input
        for (int j = 0; j < i; j++)
        {
            printf("%s ", args[j]);
        }
        printf("\n");

        if (strcmp(command, "cd") == 0)
        {
            const char *path = args[1];
            int is_path_valid = chdir(path); // Checking weather the path is valid or not

            if (is_path_valid == 0) 
            {
                printf("path = %s\n", path);
            }
            else
            {
                printf("Failed to change directory\n");
            }
        }
        else
        {
            execvp(command, args); // Execute the command

            perror("execvp"); // Print an error message if execvp fails
        }
    } while (strcmp(command, "exit") != 0);

    return 0;
}
