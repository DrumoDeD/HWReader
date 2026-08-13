// Main functions for all modules

#ifndef CORE_H
#define CORE_H

#include <stddef.h>

#define CONFIG_PATH_FILE "path.conf"
#define ERR_LOG_FILE "hwreader_error.log"

void err_interpretator(int err_code);

int get_config_path(char *key, char *path, size_t max_len);

int get_info(char *path, char *buffer, size_t max_len);

#endif