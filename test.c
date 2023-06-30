#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int saved_stdout = dup(STDOUT_FILENO); // Save the original stdout file descriptor

    char command[256];
    printf("Enter a command: ");
    fgets(command, sizeof(command), stdin);

    int fd;
    if (command[0] == '>' && command[1] != '\0')
    {
        // Extract the file name from the command
        char *filename = command + 1;

        // Open or create the file in append mode
        fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1)
        {
            perror("Error opening file");
            return 1;
        }

        // Redirect stdout to the file
        if (dup2(fd, STDOUT_FILENO) == -1)
        {
            perror("Error redirecting output");
            return 1;
        }
    }

    // Execute the command
    system(command);

    // Restore the original stdout
    if (dup2(saved_stdout, STDOUT_FILENO) == -1)
    {
        perror("Error restoring output");
        return 1;
    }

    close(saved_stdout);
    if (command[0] == '>' && command[1] != '\0')
    {
        close(fd);
    }

    return 0;
}
