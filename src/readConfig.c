#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* loadGameConf(){
    FILE *conf = fopen("/Users/turbocat009/desktopEnv/bin/background.config", "r");
    char buffer[255];
    if (conf == NULL){
        printf("Failed to open config file\n");
        return NULL;
    }

    char *imagePath = NULL;

    while (fgets(buffer, sizeof(buffer), conf)) {
        if (strncmp(buffer, "IMAGE ", 6) == 0) {
            char *pathStart = buffer + 6;
            pathStart[strcspn(pathStart, "\n")] = '\0';
            
            imagePath = malloc(strlen(pathStart) + 1);
            strcpy(imagePath, pathStart);

            printf("Image path: %s\n", imagePath);
            break;
        }
    }

    fclose(conf);
    return imagePath;
}
