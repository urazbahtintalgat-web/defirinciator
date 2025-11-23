#include "generate_folder_and_names.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>

void GenerateFolder(char * buffer, size_t buffer_size) {
    time_t now_time = time(NULL);
    struct tm * local_time = localtime(&now_time);
    
    snprintf(buffer, buffer_size, "%02d-%02d_%02d-%02d-%02d", 
             local_time->tm_mon, local_time->tm_mday,
             local_time->tm_hour, local_time->tm_min, local_time->tm_sec);

    mkdir(buffer, 0755);
}

void GenerateFilename(char * buffer, size_t buffer_size, const char * folder) {
    
    static int counter = 0;

    snprintf(buffer, buffer_size, "%s/%03d.svg", folder, counter++);

}