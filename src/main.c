#include <stdio.h>
#include <stdlib.h>
#include "../include/main.h"

#define BUILD_NUM 0
#define VER 0.0.1
#define STATE ALPHA
#define YEAR 2025

void initializeBackground(){
    printf("Drawing background\n");
    int ret = system("./bin/background"); 
    if (ret == -1)
    {
        perror("Error executing program");
    }
    printf("Background initialize failed\n");
}

int main(){
    initializeBackground();
    return 0;
}