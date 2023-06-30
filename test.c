#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100

int main() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        printf("Enter a command: ");
        fgets(command, MAX_COMMAND_LENGTH, stdin);

        // Remove trailing newline character from user input
        command[strcspn(command, "\n")] = '\0';

        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process

            // Parse the command to extract program name and arguments
            char* arguments[MAX_COMMAND_LENGTH];
            char* token = strtok(command, " ");

            int i = 0;
            while (token != NULL) {
                arguments[i++] = token;
                token = strtok(NULL, " ");
            }
            arguments[i] = NULL;  // Terminate the argument list with NULL

            // Execute the command in the background
            execvp(arguments[0], arguments);
            perror("execvp");  // execvp only returns if there's an error
            exit(EXIT_FAILURE);
        } else {
            // Parent process

            // If the command does not end with "&", wait for the child process to complete
            if (strcmp(&command[strlen(command) - 1], "&") != 0) {
                int status;
                waitpid(pid, &status, 0);

                if (WIFEXITED(status)) {
                    printf("Process %d succeeded\n", pid);
                } else {
                    printf("Process %d failed\n", pid);
                }
            } else {
                printf("Background process started with PID %d\n", pid);
            }
        }
    }

    return 0;
}
