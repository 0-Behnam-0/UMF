#include <stdio.h>
#include <string.h>

#define MAX_HISTORY 10
#define MAX_INPUT_LENGTH 100

void printHistory(char history[][MAX_INPUT_LENGTH], int count) {
    printf("History:\n");
    for (int i = 0; i < count; i++) {
        printf("%d: %s\n", i + 1, history[i]);
    }
}

int main() {
    char history[MAX_HISTORY][MAX_INPUT_LENGTH];
    int historyCount = 0;

    while (1) {
        char input[MAX_INPUT_LENGTH];

        // Prompt for user input
        printf("Enter a command: ");
        fgets(input, sizeof(input), stdin);

        // Remove trailing newline character
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "history") == 0) {
            printHistory(history, historyCount);
        } else {
            // Store the input in history
            strncpy(history[historyCount % MAX_HISTORY], input, sizeof(history[0]));
            historyCount++;
        }
    }

    return 0;
}
