#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char *username = getenv("USER");  // Get the value of the USER environment variable

    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) != 0) {
        fprintf(stderr, "Failed to get hostname.\n");
        return 1;
    }

    printf("System Name: %s\n", hostname);
    printf("User Name: %s\n", username);

    return 0;
}
