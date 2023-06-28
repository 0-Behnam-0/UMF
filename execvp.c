#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char* command = "ls";
    char* args[] = {"ls", NULL};

    int pid = fork();  // Create a child process

    if (pid == 0) {
        // Child process
        execvp(command, args);  // Execute the command
        perror("execvp");  // Print an error message if execvp fails
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Parent process
        wait(NULL);  // Wait for the child process to complete
    } else {
        // Forking failed
        perror("fork");
        exit(EXIT_FAILURE);
    }

    return 0;
}
