#include "laptop.h"
#include "core.h"

int get_laptop_vendor(char *buffer, size_t max_len){
char path[256]; 
int status = get_config_path("LAPTOP_VENDOR_PATH", path, sizeof(path));
if (status==0){
    status = get_info(path, buffer, max_len);
    if (status ==0){
        return 0; 
        }
    err_interpretator(status);
    return 202;
    }  
err_interpretator(status);
return 201;
}

int get_laptop_model(char *buffer, size_t max_len){
char path[256]; 
int status = get_config_path("LAPTOP_MODEL_PATH", path, sizeof(path));
if (status==0){
    status = get_info(path, buffer, max_len);
    if (status ==0){
        return 0; 
        }
    err_interpretator(status);
    return 204;
    }  
err_interpretator(status);
return 203; 
}

