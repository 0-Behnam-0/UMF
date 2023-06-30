#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARG 20

typedef struct
{
    int pid;
} Process;

int main()
{
    char *USERNAME = getenv("USER");
    char HOSTNAME[256];
    gethostname(HOSTNAME, sizeof(HOSTNAME));

    char COMMAND[100];
    Process backgroundProcesses[MAX_ARG]; // Array to store background processes
    int bgProcessCount = 0;               // Counter for background processes

    do
    {
        char calcwd[1000];
        char *dir_path = getcwd(calcwd, sizeof(calcwd));
        if (dir_path != NULL)
        {
            printf("(%s@%s)-[~%s] $ ", USERNAME, HOSTNAME, dir_path);
        }
        else if (dir_path == NULL)
        {
            printf("(%s@%s)-[NULL] $ ", USERNAME, HOSTNAME);
        }
        else
        {
            perror("Error(getcwd)");
        }

        fgets(COMMAND, sizeof(COMMAND), stdin);
        COMMAND[strcspn(COMMAND, "\n")] = '\0';

        if (strlen(COMMAND) == 0)
        {
            continue;
        }

        char *token;
        char *args[MAX_ARG];

        int i = 0;
        token = strtok(COMMAND, " ");
        while (token != NULL && i < MAX_ARG + 1)
        {
            args[i++] = token;
            token = strtok(NULL, " ");
        }

        args[i] = NULL;
        char *last_arg = args[i - 1];

        if (strcasecmp(COMMAND, "exit") == 0)
        {
            printf("Exiting...\n");
            break;
        }
        else if (strcasecmp(COMMAND, "cd") == 0)
        {
            const char *path = args[1];
            int is_path_valid = chdir(path);
            if (is_path_valid != 0)
            {
                printf("Failed to change directory\n");
            }
            continue;
        }
        else if (strcasecmp(COMMAND, "globalusage") == 0)
        {
            printf("+--------------------------------------------+\n");
            printf("¦ Uncomplicated Microterminal Framework(UMF) ¦\n");
            printf("¦ by Mahdi Mohamadiha.                       ¦\n");
            printf("+--------------------------------------------+\n");
        }
        else if (strcasecmp(COMMAND, "bgprocess") == 0)
        { // Display background processes
            printf("Background Processes:\n");
            for (int j = 0; j < bgProcessCount; j++)
            {
                printf("PID: %d\n", backgroundProcesses[j].pid);
            }
        }
        else
        {
            pid_t process_id = fork();

            if (process_id == 0)
            {
                execvp(COMMAND, args);
                perror("Error(exec)");
                exit(EXIT_FAILURE);
            }
            else if (process_id > 0)
            {
                if (strcmp(last_arg, "&") != 0)
                {
                    int status;
                    waitpid(process_id, &status, 0);

                    if (WIFEXITED(status))
                    {
                        printf("Process %d succeeded\n", process_id);
                    }
                    else
                    {
                        printf("Process %d failed\n", process_id);
                    }
                }
                else
                {
                    Process newBgProcess;
                    newBgProcess.pid = process_id;
                    backgroundProcesses[bgProcessCount++] = newBgProcess;
                    printf("Background process started with PID %d\n", process_id);
                }
            }
            else
            {
                perror("Error(fork)");
            }
        }
    } while (1);

    return 0;
}
