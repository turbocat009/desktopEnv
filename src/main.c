#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void initializeBackground() {
    putenv("DISPLAY=:0");

    pid_t pid_background = fork();
    if (pid_background == 0) {
        printf("Drawing background\n");

        char *args[] = {"./bin/background", NULL};
        if (execvp(args[0], args) == -1) {
            perror("Error executing background process");
            exit(1); 
        }
    }
    else if (pid_background < 0) {
        perror("Failed to fork for background");
    }

    pid_t pid_bar = fork();
    if (pid_bar == 0) {
        printf("Drawing top bar\n");

        char *args[] = {"./bin/topBar", NULL};
        if (execvp(args[0], args) == -1) {
            perror("Error executing top bar process");
            exit(1); 
        }
    }
    else if (pid_bar < 0) {
        perror("Failed to fork for top bar");
    }
}

int main() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working dir: %s\n", cwd);
    }
    else {
        perror("getcwd() error");
    }
    initializeBackground();

    return 0;
}
