#include "cpu.h"
#include "core.h"

#include <string.h>
#include <stdio.h>

int cpuinfo_parcer(char *key, char *buffer, size_t max_len){
char path[256]; 
if (get_config_path("CPU_INFO_PATH", path, sizeof(path))==0){
    FILE *file = fopen(path, "r");
    char line[512];
    size_t key_len = strlen(key);
    if (file != NULL){
        while (fgets(line, sizeof(line), file)){
            if (strncmp(line, key, key_len)==0){
                char *colon = strchr(line, ':');
                if (colon != NULL){
                    char *value = colon+2;
                    value[strcspn(value, "\n")]=0;
                    strncpy(buffer, value, max_len);
                    fclose(file);
                    return 0;
                    }
                }
            }
        fclose(file);
        strncpy(buffer, "N/A", max_len);
        } 
    return 402;
    }    
return 401;
}

int get_cpu_name(char *buffer, size_t max_len){
    int status = cpuinfo_parcer("model name", buffer, max_len);
    if (status==0){
        return 0;
        }
    err_interpretator(status);
}

int get_cpu_vendor(char *buffer, size_t max_len){
    int status = cpuinfo_parcer("vendor_id", buffer, max_len);
    if (status==0){
        return 0;
        }
    err_interpretator(status);
}

int get_cpu_cores(char *buffer, size_t max_len){
    int status = cpuinfo_parcer("cpu cores", buffer, max_len);
    if (status==0){
        return 0;
        }
    err_interpretator(status);
}

int get_cpu_siblings(char *buffer, size_t max_len){
    int status = cpuinfo_parcer("siblings", buffer, max_len);
    if (status==0){
        return 0;
        }
    err_interpretator(status);
}

int get_cpu_L3cache(char *buffer, size_t max_len){
    int status = cpuinfo_parcer("cache size", buffer, max_len);
    if (status==0){
        return 0;
        }
    err_interpretator(status);
}