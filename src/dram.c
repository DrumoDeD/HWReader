#include "dram.h"
#include "core.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int get_module_count(int *count){
char cmd[256]=POLKIT_COMMAND;
char path[256];
*count = 0;
int status = 0;
if (get_config_path("RAM_INFO_PATH", path, sizeof(path))==0){
    char fullcmd[512];
    snprintf(fullcmd, sizeof(fullcmd), "%s > %s", cmd, path);
    int sys_status = system(fullcmd);
    if (sys_status != 0) {
        return 502;
        }
    FILE *file = fopen(path,"r");
    char line[512];
    while (fgets(line,sizeof(line), file)){
        if (strstr(line, "Memory Device") !=NULL){
            (*count)++;
            }   
        }
    fclose(file);
    return 0;
    }
return 501;
}

typedef enum{
FIELD_VENDOR,
FIELD_PART_NUM,
FIELD_VOLUME,
FIELD_TYPE,
FIELD_FREQ,
FIELD_RANK,
FIELD_UNKNOWN
}RamField;

static RamField detector(const char *line){
if (strstr(line, "Configured Memory Speed")) return FIELD_UNKNOWN;
if (strstr(line, "Type Detail")) return FIELD_UNKNOWN; 
if (strstr(line, "Manufacturer")) return FIELD_VENDOR;
if (strstr(line, "Part Number")) return FIELD_PART_NUM;
if (strstr(line, "Size")) return FIELD_VOLUME;
if (strstr(line, "Type")) return FIELD_TYPE;
if (strstr(line, "Speed")) return FIELD_FREQ;
if (strstr(line, "Rank")) return FIELD_RANK;
return FIELD_UNKNOWN;    
}

int get_dram(RamModuleInfo *modules, int max_modules){
for (int i=0;i<max_modules; i++){
    strcpy(modules[i].vendor, "N/A");
    strcpy(modules[i].part_num, "N/A");
    strcpy(modules[i].volume, "N/A");
    strcpy(modules[i].type, "N/A");
    strcpy(modules[i].freq, "N/A");
    strcpy(modules[i].rank, "N/A");
    }
char path[256];
if (get_config_path("RAM_INFO_PATH", path, sizeof(path))==0){
    FILE *file = fopen(path, "r");
    char line[512];
    int current_module=-1;
    while (fgets(line, sizeof(line), file)){
        line[strcspn(line, "\n")]=0;
        if (strstr(line, "Memory Device")!=NULL){
            current_module++;
            if (current_module>=max_modules) break;
            continue;
            }
        if (current_module<0) continue;
        char *colon = strchr(line, ':');
        if (colon !=NULL){
            char *value=colon+2;
            switch (detector(line)){
                case FIELD_VENDOR:
                   strcpy(modules[current_module].vendor, value); 
                   break;
                case FIELD_PART_NUM:
                    strcpy(modules[current_module].part_num, value);
                    break;
                case FIELD_VOLUME:
                    strcpy(modules[current_module].volume, value);
                    break;
                case FIELD_TYPE:
                    strcpy(modules[current_module].type, value);
                    break;
                case FIELD_FREQ:
                    strcpy(modules[current_module].freq, value);
                    break;
                case FIELD_RANK:
                   strcpy(modules[current_module].rank, value); 
                   break;    
                default:
                    break;
                }
            }   
        }
    fclose(file);
    remove(path);
    return 0;
    }
return 1;    
}