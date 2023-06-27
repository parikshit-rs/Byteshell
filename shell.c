#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10
#define MAX_HISTORY 50

char command_history[MAX_HISTORY][MAX_COMMAND_LENGTH];
int history_count = 0;

void cd_command(char *directory) {
    if (directory == NULL) {
        chdir(getenv("HOME"));
    } else {
        if (chdir(directory) != 0) {
            printf("Directory not found.\n");
        }
    }
}

void exit_command() {
    exit(0);
}

void help_command() {
    printf("Available commands:\n");
    printf("cd [directory] - Change the current working directory.\n");
    printf("exit - Exit the shell program.\n");
    printf("help - Display information about the available commands.\n");
    printf("bind [key] [command] - Bind a specific key to execute a command.\n");
    printf("bg [command] - Execute a command in the background.\n");
    printf("caller [command] - Execute a command as if it was called from the shell.\n");
    printf("history - Display the command history.\n");
}

void bind_command(char *key, char *command) {
    // Implement the bind command logic here
    printf("Bind command not implemented.\n");
}

void bg_command(char *command) {
    // Implement the bg command logic here
    printf("Background command not implemented.\n");
}

void caller_command(char *command) {
    // Implement the caller command logic here
    printf("Caller command not implemented.\n");
}

void history_command() {
    int start = (history_count - MAX_HISTORY) >= 0 ? history_count - MAX_HISTORY : 0;
    for (int i = start; i < history_count; i++) {
        printf("%d. %s\n", i+1, command_history[i % MAX_HISTORY]);
    }
}

void execute_command(char *args[]) {
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
            printf("Command not found.\n");
            exit(EXIT_FAILURE);
        }
    } else if (pid < 0) {
        // Error forking
        printf("Error forking process.\n");
    } else {
        // Parent process
        wait(NULL);
    }
}

void add_to_history(char *command) {
    strncpy(command_history[history_count % MAX_HISTORY], command, MAX_COMMAND_LENGTH);
    history_count++;
}

int main() {
    char input[MAX_COMMAND_LENGTH];
    char *args[MAX_ARGS];
    char *token;

    while (1) {
        printf("> ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // Remove trailing newline

        add_to_history(input);

        token = strtok(input, " ");
        int i = 0;
        while (token != NULL) {
            args[i] = token;
            token = strtok(NULL, " ");
            i++;
        }
        args[i] = NULL;

        if (args[0] == NULL) {
            continue; // Empty command, prompt again
        }

        if (strcmp(args[0], "cd") == 0) {
            cd_command(args[1]);
        } else if (strcmp(args[0], "exit") == 0) {
            exit_command();
        } else if (strcmp(args[0], "help") == 0) {
            help_command();
        } else if (strcmp(args[0], "bind") == 0 && args[1] != NULL && args[2] != NULL) {
            bind_command(args[1], args[2]);
        } else if (strcmp(args[0], "bg") == 0 && args[1] != NULL) {
            bg_command(args[1]);
        } else if (strcmp(args[0], "caller") == 0 && args[1] != NULL) {
            caller_command(args[1]);
        } else if (strcmp(args[0], "history") == 0) {
            history_command();
        } else {
            execute_command(args);
        }
    }

    return 0;
}
