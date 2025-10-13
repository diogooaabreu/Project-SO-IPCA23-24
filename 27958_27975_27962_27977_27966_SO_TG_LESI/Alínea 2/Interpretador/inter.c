#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100
#define SUCCESS_EXIT_CODE 0

void execute_command(char *command) {
    pid_t pid = fork();

    if (pid < 0) {
        // Error forking
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        char *args[MAX_COMMAND_LENGTH];
        char *token = strtok(command, " ");
        int i = 0;

        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        execvp(args[0], args);

        // execvp only returns on error
        perror("Execution failed");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            printf("Terminou comando %s com código %d\n", strtok(command, " "), WEXITSTATUS(status));
        }
    }
}

int main() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        printf("%% ");
        fflush(stdout);

        if (fgets(command, sizeof(command), stdin) == NULL) {
            break;
        }

        // Remove trailing newline
        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "termina") == 0) {
            break;
        }

        execute_command(command);
    }

    return EXIT_SUCCESS;
}
