#pragma once
#include "customMemoryLeakTracker.h"
#include "commons.h"

// WIP

void compute_keyword_stats() {
    FILE* fp;
    char path[1024];
    fp = popen("/bin/find ../_Assignment_Tests/ -type f -iname *.S", "r");
    while (fgets(path, sizeof(path), fp) != NULL) {
        path[strlen(path)-1] = '\0';
        printf("%s\n", path);
        FILE* file = fopen(path, "r");

        if(file == NULL)
            continue;

        char* line = NULL;
        size_t len = 0;
        int read;
        while((read = getline(&line, &len, file)) != -1) {
            printf("%lu %s", read, line);
            char* current = NULL;
            while((current = strtok(line," "))) {
                if(current[0] >= '0' || current[0] <= '9')
                    break;
                switch(current[0]) {
                    case '#':
                        break;
                    case '.':{
                        break;
                    }
                }
                //strcpy();
                break;
            }
        }
        //free(line);

        fclose(file);
    }
    pclose(fp);


}