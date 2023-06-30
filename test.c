#include <stdio.h>
#include <unistd.h>

int main() {
    char cwd[1024]; // Buffer to hold the current working directory
    
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working directory: %s\n", cwd);
    } else {
        perror("getcwd() error");
        return 1;
    }
    
    return 0;
}
