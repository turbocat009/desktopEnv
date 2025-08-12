#include <stdio.h>
#include <stdlib.h>
#include "../include/main.h"

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