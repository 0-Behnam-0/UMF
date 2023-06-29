// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/wait.h> // for wait syntax


// int main() {
//     char* command = "pwd";
//     char* args[] = {"pwd", NULL};

//     int pid = fork();  // Create a child process

//     if (pid == 0) {
//         // Child process
//         execvp(command, args);  // Execute the command
//         perror("execvp");  // Print an error message if execvp fails
//         exit(EXIT_FAILURE);
//     } else if (pid > 0) {
//         // Parent process
//         wait(NULL);  // Wait for the child process to complete
//     } else {
//         // Forking failed
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }

//     return 0;
// }


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    char command[100];  // Buffer to hold the user input command
    printf("Enter a command: ");
    fgets(command, sizeof(command), stdin);

    // Remove trailing newline character from the command
    command[strcspn(command, "\n")] = '\0';

    // Split the command into tokens based on spaces
    char* token;
    char* args[20];  // Maximum 20 arguments including the command itself
    int i = 0;

    token = strtok(command, " ");
    while (token != NULL && i < 19) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;  // Set the last element to NULL

    execvp(args[0], args);  // Execute the command

    perror("execvp");  // Print an error message if execvp fails
    return 0;
}
