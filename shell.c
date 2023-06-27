#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_HISTORY_SIZE 10

char* history[MAX_HISTORY_SIZE];
int history_count = 0;

typedef struct {
    char key[10];
    char command[MAX_COMMAND_LENGTH];
} Binding;

Binding bindings[10];
int binding_count = 0;

void print_prompt() {
    printf("Shell> ");
}

void read_command(char* command) {
    fgets(command, MAX_COMMAND_LENGTH, stdin);
    command[strcspn(command, "\n")] = '\0';  // Remove newline character
}

void add_to_history(const char* command) {
    if (history_count < MAX_HISTORY_SIZE) {
        history[history_count] = strdup(command);
        history_count++;
    } else {
        free(history[0]);
        for (int i = 1; i < MAX_HISTORY_SIZE; i++) {
            history[i - 1] = history[i];
        }
        history[MAX_HISTORY_SIZE - 1] = strdup(command);
    }
}

void display_history() {
    for (int i = 0; i < history_count; i++) {
        printf("%d. %s\n", i + 1, history[i]);
    }
}

void execute_command(char* command) {
    pid_t pid = fork();

    if (pid == -1) {
        printf("Error: Failed to fork\n");
        return;
    } else if (pid == 0) {
        // Child process
        char* args[MAX_COMMAND_LENGTH];
        int arg_count = 0;

        // Split command into arguments
        char* token = strtok(command, " ");
        while (token != NULL) {
            args[arg_count] = token;
            arg_count++;
            token = strtok(NULL, " ");
        }
        args[arg_count] = NULL;

        if (execvp(args[0], args) == -1) {
            printf("Error: Failed to execute command\n");
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent process
        wait(NULL);
    }
}

void cd_command(char* directory) {
    if (chdir(directory) == -1) {
        printf("Error: Failed to change directory\n");
    }
}

void exit_command() {
    exit(0);
}

void help_command() {
    printf("Shell Program Help:\n");
    printf("cd <directory>    - Change directory\n");
    printf("exit              - Exit the shell\n");
    printf("help              - Display this help message\n");
    printf("execute <command> - Execute a command\n");
    printf("wait              - Wait for child processes to finish\n");
    printf("fork              - Create a child process\n");
    printf("history           - Display command history\n");
    printf("bind <key> <cmd>  - Bind a command to a key\n");
    printf("caller            - Display the caller process ID\n");
    printf("bg <command>      - Execute a command in the background\n");
}

void bind_command(char* key, char* command) {
    if (binding_count < 10) {
        strcpy(bindings[binding_count].key, key);
        strcpy(bindings[binding_count].command, command);
        binding_count++;
        printf("Command '%s' is bound to key '%s'\n", command, key);
    } else {
        printf("Error: Maximum binding limit reached\n");
    }
}

void caller_command() {
    pid_t parent_pid = getppid();
    printf("Parent Process ID: %d\n", parent_pid);
}

void bg_command(char* command) {
    pid_t pid = fork();

    if (pid == -1) {
        printf("Error: Failed to fork\n");
        return;
    } else if (pid == 0) {
        // Child process
        execute_command(command);
        exit(0);
    } else {
        // Parent process
        printf("Background process started with PID: %d\n", pid);
    }
}

int main() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        print_prompt();
        read_command(command);

        add_to_history(command);

        if (strcmp(command, "exit") == 0) {
            exit_command();
        } else if (strcmp(command, "help") == 0) {
            help_command();
        } else if (strncmp(command, "execute", 7) == 0) {
            char* cmd = command + 8;  // Skip "execute "
            execute_command(cmd);
        } else if (strcmp(command, "wait") == 0) {
            wait(NULL);
        } else if (strcmp(command, "fork") == 0) {
            fork();
        } else if (strcmp(command, "history") == 0) {
            display_history();
        } else if (strncmp(command, "cd", 2) == 0) {
            char* directory = command + 3;  // Skip "cd "
            cd_command(directory);
        } else if (strncmp(command, "bind", 4) == 0) {
            char key[10];
            char cmd[MAX_COMMAND_LENGTH];
            sscanf(command, "%*s %s %s", key, cmd);
            bind_command(key, cmd);
        } else if (strcmp(command, "caller") == 0) {
            caller_command();
        } else if (strncmp(command, "bg", 2) == 0) {
            char* cmd = command + 3;  // Skip "bg "
            bg_command(cmd);
        } else {
            int found = 0;
            for (int i = 0; i < binding_count; i++) {
                if (strcmp(command, bindings[i].key) == 0) {
                    execute_command(bindings[i].command);
                    found = 1;
                    break;
                }
            }
            if (!found) {
                printf("Error: Command not found\n");
            }
        }
    }

    return 0;
}
