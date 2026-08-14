// Get information about device

#ifndef LAPTOP_H
#define LAPTOP_H

#include <stddef.h>

//#define LAPTOP_VENDOR_PATH "/sys/class/dmi/id/sys_vendor"
//#define LAPTOP_MODEL_PATH "/sys/class/dmi/id/product_name"

int get_laptop_vendor(char *buffer, size_t max_len);
int get_laptop_model(char *buffer, size_t max_len);

#endif