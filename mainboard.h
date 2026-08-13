// Get information about mainboard

#ifndef MAINBOARD_H
#define MAINBOARD_H

#include <stddef.h>

int get_mb_name(char *buffer, size_t max_len);

int get_mb_chipset(char *buffer, size_t max_len);

#endif