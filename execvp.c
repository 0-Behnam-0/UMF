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
        char calcwd[1000];                               // Buffer to hold the calculate current working directory(calcwd)
        char *dir_path = getcwd(calcwd, sizeof(calcwd)); // Get the path and store into 'dir_path'
        if (dir_path != NULL)                            // Handling path errors
        {
            printf("%s $ ", dir_path);
        }
        else if (dir_path == NULL)
        {
            printf("[NULL] $ ");
        }
        else
        {
            perror("Error(getcwd)");
        }
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

        if (strcasecmp(command, "exit") == 0) // Check for exiting input
        {
            printf("Exiting...\n");
            sleep(1);
            printf("\033[2J");
            break;
        }
        if (strcasecmp(command, "cd") == 0) // 'strcasecmp' is the same as 'strcmp' but it ignores the cases
        {
            const char *path = args[1];
            int is_path_valid = chdir(path); // Checking weather the path is valid or not
            if (is_path_valid != 0)
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
                perror("Error(exec)"); // Print an error message if execvp fails
                exit(1);               // Kill the child if error rised
            }
            else if (process_id > 0)
            {
                int status;
                wait(&status); // Wait for the child process to complete
            }
            else
            {
                perror("Error(fork)"); // If creating new process via fork falis, error will be printed
            }
        }
    } while (1); // Keep the program alive

    return 0;
}
