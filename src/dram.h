// Get information about DRAM

#ifndef DRAM_H
#define DRAM_H

#include <stddef.h>

#define POLKIT_COMMAND "usr/sbin/dmidecode -t 17 2> /dev/null"

typedef struct{
char vendor[128];
char part_num[128];
char volume[32];
char type[16];
char freq[32];
char rank[16];
}RamModuleInfo;

int get_module_count(int *count);
int get_dram(RamModuleInfo *modules, int max_modules);

#endif