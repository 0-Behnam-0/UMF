#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    const int MAX_ARG = 20; // Set maximum arg size which is readable only
    char *USENAME = getenv("USER");
    char HOSTNAME[100];
    gethostname(HOSTNAME, sizeof(HOSTNAME)); // Store hostname

    char COMMAND[100]; // Buffer to hold the user input command
    do
    {
        char calcwd[1000];                               // Buffer to hold the calculate current working directory(calcwd)
        char *dir_path = getcwd(calcwd, sizeof(calcwd)); // Get the path and store into 'dir_path'
        if (dir_path != NULL)                            // Handling path errors
        {
            printf("(%s@%s)-[~%s] $ ", USENAME, HOSTNAME, dir_path);
        }
        else if (dir_path == NULL)
        {
            printf("(%s@%s)-[NULL] $ ", USENAME, HOSTNAME);
        }
        else
        {
            perror("Error(getcwd)");
        }

        fgets(COMMAND, sizeof(COMMAND), stdin); // User input
        COMMAND[strcspn(COMMAND, "\n")] = '\0'; // Remove newline character from the command('\n' will replaced with '\0')
        if (strlen(COMMAND) == 0)               // Skiping empty inputs
        {
            continue;
        }

        char *token;         // Split the command into tokens based on spaces
        char *args[MAX_ARG]; // Maximum arguments excluding the command itself

        int i = 0;
        token = strtok(COMMAND, " "); // First element of input parsed into token
        while (token != NULL && i < MAX_ARG + 1)
        {
            args[i++] = token;
            token = strtok(NULL, " ");
        }

        args[i] = NULL; // Set the last element to NULL
        /*
        Warning: Ignoring this line of code cause the pointer moves into inaccessible memory address,
         and finally 'Bad address' error will be rised!
        */

        char *last_arg = args[i - 1]; // Get the last argument of input

        int redirect_flag = 0;
        for (int cnt = 0; cnt < i; cnt++)
        {
            if (strcmp(args[cnt], ">") == 0)
            {
                redirect_flag = 1;
                for (int ele = cnt - 1; ele > -1; ele--) // Original stdout
                {
                    printf("o: %s\n", args[ele]);
                }
                printf("--------\n");
                for (int ele = cnt + 1; ele < i; ele++) // File name
                {
                    printf("f: %s\n", args[ele]);
                }
            }
        }
        printf("redirect_flag = %d\n", redirect_flag);

        if (strcasecmp(COMMAND, "exit") == 0) // Check for exiting input
        {
            printf("Exiting...\n");
            // sleep(1);
            printf("\033[2J");
            break;
        }
        else if (strcasecmp(COMMAND, "cd") == 0) // 'strcasecmp' is the same as 'strcmp' but it ignores the cases
        {
            const char *path = args[1];
            int is_path_valid = chdir(path); // Checking weather the path is valid or not
            if (is_path_valid != 0)
            {
                printf("Failed to change directory\n");
            }
        }
        else if (strcasecmp(COMMAND, "globalusage") == 0) // Programmer info
        {
            printf("+--------------------------------------------+\n");
            printf("¦ Uncomplicated Microterminal Framework(UMF) ¦\n");
            printf("¦ by Mahdi Mohamadiha.                       ¦\n");
            printf("+--------------------------------------------+\n");
        }
        else // This statement created to prevent closing program when external commands are entered
        {
            pid_t process_id = fork(); // Create a new process insed the program with pid stored in 'process_id' via pid_t

            if (process_id == 0) // Child process
            {
                execvp(COMMAND, args); // Execute the command
                perror("Error(exec)"); // Print an error message if execvp fails
                exit(EXIT_FAILURE);    // Kill the child if error rised
            }
            else if (process_id > 0) // Parent process
            {
                if (strcmp(last_arg, "&") != 0)
                {
                    int status;
                    waitpid(process_id, &status, 0);

                    if (!WIFEXITED(status)) // Check the child process finished normally or not
                    {
                        printf("Process %d failed\n", process_id);
                    }
                }
                else
                {
                    printf("Background process started with PID %d\n", process_id);
                }
            }
            else // Fork failing
            {
                perror("Error(fork)"); // If creating new process via fork falis, error will be printed
            }
        }
    } while (1); // Keep the program alive

    return 0;
}
