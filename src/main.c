#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/main.h"

#define BUILD_NUM 0
#define VER 0.0.1
#define STATE ALPHA
#define YEAR 2025

void initializeBackground(){
    pid_t pid_background = fork();
    if (pid_background == 0){
        printf("Drawing background\n");
        int ret = system("./bin/background"); 
        if (ret == -1) {
            perror("Error executing program");
        }
    } else if (pid_background < 0) {
        perror("Failed to fork for background");
    }
    
    pid_t pid_xterm = fork();
    if (pid_xterm == 0) {
        printf("Drawing background\n");
        int ret = system("xterm");
        if (ret == -1)
        {
            perror("Error executing program");
        }
    } else if (pid_xterm < 0) {
        perror("Failed to fork for background");
    }
}

int main(){
    initializeBackground();
    return 0;
}