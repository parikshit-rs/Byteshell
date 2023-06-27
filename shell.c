#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10
#define MAX_HISTORY_SIZE 10

// Function prototypes
void cd(char* directory);
void exitShell();
void helpInfo();
void executeCommand(char* command, char* arguments[]);
void printHistory(char* history[], int size);

int main() {
    char command[MAX_COMMAND_LENGTH];
    char* arguments[MAX_ARGUMENTS];
    char* history[MAX_HISTORY_SIZE];
    int historySize = 0;

    while (1) {
        printf("> ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0';

        // Tokenize the command
        char* token = strtok(command, " ");
        int argIndex = 0;
        while (token != NULL && argIndex < MAX_ARGUMENTS - 1) {
            arguments[argIndex] = token;
            token = strtok(NULL, " ");
            argIndex++;
        }
        arguments[argIndex] = NULL;

        // Add command to history
        if (historySize < MAX_HISTORY_SIZE) {
            history[historySize] = strdup(command);
            historySize++;
        } else {
            free(history[0]);
            for (int i = 1; i < MAX_HISTORY_SIZE; i++) {
                history[i - 1] = history[i];
            }
            history[MAX_HISTORY_SIZE - 1] = strdup(command);
        }

        // Execute command
        if (strcmp(arguments[0], "cd") == 0) {
            cd(arguments[1]);
        } else if (strcmp(arguments[0], "exit") == 0) {
            exitShell();
        } else if (strcmp(arguments[0], "help") == 0) {
            helpInfo();
        } else if (strcmp(arguments[0], "execute") == 0) {
            executeCommand(arguments[1], &arguments[1]);
        } else if (strcmp(arguments[0], "wait") == 0) {
            wait(NULL);
        } else if (strcmp(arguments[0], "fork") == 0) {
            pid_t pid = fork();
            if (pid == 0) {
                printf("Child process\n");
            } else if (pid > 0) {
                printf("Parent process\n");
            } else {
                printf("Fork failed\n");
            }
        } else if (strcmp(arguments[0], "history") == 0) {
            printHistory(history, historySize);
        } else {
            printf("Command not found: %s\n", arguments[0]);
        }
    }

    return 0;
}

void cd(char* directory) {
    if (directory != NULL) {
        if (chdir(directory) != 0) {
            printf("Directory not found: %s\n", directory);
        }
    } else {
        printf("Missing argument for 'cd' command\n");
    }
}

void exitShell() {
    exit(0);
}

void helpInfo() {
    printf("This is a basic shell program.\n");
    printf("Available commands: cd, exit, help, execute, wait, fork, history\n");
}

void executeCommand(char* command, char* arguments[]) {
    pid_t pid = fork();
    if (pid == 0) {
        execvp(command, arguments);
        printf("Command not found: %s\n", command);
        exit(0);
    } else if (pid < 0) {
        printf("Fork failed\n");
    }
}

void printHistory(char* history[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%s\n", history[i]);
    }
}
