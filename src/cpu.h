// Get information about CPU

#ifndef CPU_H
#define CPU_H

#include <stddef.h>

int cpuinfo_parcer(char *key, char *buffer, size_t max_len);

int get_cpu_name(char *buffer, size_t max_len);
int get_cpu_vendor(char *buffer, size_t max_len);
int get_cpu_cores(char *buffer, size_t max_len);
int get_cpu_siblings(char *buffer, size_t max_len);
int get_cpu_L3cache(char *buffer, size_t max_len);

#endif