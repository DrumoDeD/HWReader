#include "core.h"

#include <stdio.h>
#include <string.h>

void err_interpretator(int err_code){
FILE *log_file = fopen(ERR_LOG_FILE, "a");
if (log_file == NULL) {
        return;
    }
char desc[256];
switch (err_code)
    {
    case 101: strcpy(desc,"Configuration file missing path.conf");
        break;
    case 102: strcpy(desc,"Configuration file error");
        break;
    case 103: strcpy(desc,"Source file not found");
        break;
    case 201: strcpy(desc,"LAPTOP_VENDOR_PATH key was expected in path.conf");
        break;
    case 202: strcpy(desc,"LAPTOP_VENDOR_PATH invalid path. Check path.conf");
        break;
    case 203: strcpy(desc,"LAPTOP_MODEL_PATH key was expected in path.conf");
        break;
    case 204: strcpy(desc,"LAPTOP_MODEL_PATH invalid path. Check path.conf");
        break;
    case 301: strcpy(desc,"MB_NAME_PATH key was expected in path.conf");
        break;
    case 302: strcpy(desc,"MB_NAME_PATH invalid path. Check path.conf");
        break;
    case 401: strcpy(desc,"CPU_INFO_PATH key was expected in path.conf");
        break;
    case 402: strcpy(desc,"File /cpuinfo not found. Check path.conf");
        break;
    case 501: strcpy(desc,"RAM_INFO_PATH key was expected in path.conf");
        break;      
    case 502: strcpy(desc,"DMI error");
        break; 
    default: strcpy(desc,"Unknown error");
        break;
    }
fprintf(log_file, "%d : %s\n", err_code, desc);
fclose(log_file);
printf("  [ERROR] %d : %s\n", err_code, desc);
}

int get_config_path (char *key, char *path, size_t max_len){
FILE *file = fopen(CONFIG_PATH_FILE, "r");
if (file != NULL){
    if (strcmp(key, "TEST_CONFIG") == 0) {
            fclose(file); 
            return 0;    
        }
    char line[512];
    while (fgets(line, sizeof(line), file)){
        line[strcspn(line, "\n")] = 0;
        char *equal_sign = strchr(line, '=');
        if (equal_sign != NULL){
            *equal_sign='\0';
            char *current_key = line;
            char *current_value = equal_sign + 1;
            if (strcmp(current_key, key) == 0){
                strncpy(path, current_value, max_len);
                fclose(file);
                return 0;
                }
            }
        }
    fclose(file);
    return 102;
    }
return 101;
}

int get_info(char *path, char *buffer, size_t max_len){
FILE *file = fopen(path, "r");
if (file != NULL){
    if (fgets (buffer, max_len, file)){
        buffer[strcspn(buffer,"\n")] = 0;
        fclose(file);
        return 0;
        }
    fclose(file);
    strncpy(buffer, "N/A", max_len);
    }
return 103;
}

