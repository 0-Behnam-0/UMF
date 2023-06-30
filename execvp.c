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

        command[strcspn(command, "\n")] = '\0'; // Remove newline character from the command('\n' will replaced with '\0')

        char *token;            // Split the command into tokens based on spaces
        const int arg_max = 20; // Set maximum arg size which is readable only
        char *args[arg_max];    // Maximum arguments excluding the command itself

        int i = 0;
        token = strtok(command, " "); // First element of input parsed into token
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

        if (strcasecmp(command, "exit") == 0) // Check for exiting input
        {
            break;
        }
        if (strcasecmp(command, "cd") == 0) // 'strcasecmp' is the same as 'strcmp' but it ignores the cases
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
        else // This statement created to prevent closing program when external commands are enterd
        {
            pid_t process_id = fork(); // Create a new process insed the program with pid stored in 'process_id' via pid_t
            if (process_id == 0)
            {
                execvp(command, args); // Execute the command
                perror("execvp");      // Print an error message if execvp fails
                exit(1);               // Kill the child if error rised
            }
            else if (process_id > 0)
            {
                int status;
                wait(&status); // Wait for the child process to complete
            }
            else
            {
                perror("fork"); // If creating new process via fork falis, error will be printed
            }
        }
    } while (1); // Keep the program alive

    return 0;
}
