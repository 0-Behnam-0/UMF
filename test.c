#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    char command[100]; // Buffer to hold the user input command

    do
    {
        printf("Enter a command: ");
        fgets(command, sizeof(command), stdin); // User input

        command[strcspn(command, "\n")] = '\0'; // Remove newline character from the command ('\n' will be replaced with '\0')

        char *token;            // Split the command into tokens based on spaces
        const int arg_max = 20; // Set maximum arg size which is readable only
        char *args[arg_max];    // Maximum arguments excluding the command itself

        int i = 0;
        token = strtok(command, " "); // First element of command parsed into token
        while (token != NULL && i < arg_max)
        {
            args[i++] = token;
            token = strtok(NULL, " ");
        }

        args[i] = NULL; // Set the last element to NULL

        printf("args = "); // Printing the user's input
        for (int j = 0; j < i; j++)
        {
            printf("%s ", args[j]);
        }
        printf("\n");

        if (strcasecmp(args[0], "cd") == 0)
        {
            const char *path = args[1];
            int is_path_valid = chdir(path); // Checking whether the path is valid or not

            if (is_path_valid == 0)
            {
                printf("path = %s\n", path);
            }
            else
            {
                printf("Failed to change directory\n");
            }
        }
        else if (strcasecmp(args[0], "exit") == 0)
        {
            break; // Exit the loop when "exit" command is entered
        }
        else
        {
            pid_t pid = fork(); // Create a new process

            if (pid == 0) // Child process
            {
                execvp(args[0], args); // Execute the command

                perror("execvp"); // Print an error message if execvp fails
                exit(1);          // Terminate the child process if execvp fails
            }
            else if (pid > 0) // Parent process
            {
                int status;
                wait(&status); // Wait for the child process to complete
            }
            else
            {
                perror("fork"); // Print an error message if fork fails
            }
        }

    } while (1);

    return 0;
}
