#include "mainboard.h"
#include "core.h"

#include <string.h>
#include <pci/pci.h>


int get_mb_name(char *buffer, size_t max_len){
char path[256]; 
int status = get_config_path("MB_NAME_PATH", path, sizeof(path));
if (status==0){
    status = get_info(path, buffer, max_len);
    if (status ==0){
        return 0; 
        }
    err_interpretator(status);
    return 302;
    }  
err_interpretator(status);
return 301;
}

int get_mb_chipset(char *buffer, size_t max_len){
struct pci_access *pacc;
struct pci_dev *dev;
char namebuf[256];
pacc = pci_alloc();
pci_init(pacc);
pci_scan_bus(pacc);
strncpy(buffer, "N/A", max_len);
for (dev = pacc->devices; dev; dev = dev->next){
    pci_fill_info(dev, PCI_FILL_IDENT | PCI_FILL_CLASS);
    if (dev->device_class==0x0601){
        pci_lookup_name(pacc, namebuf, sizeof(namebuf), PCI_LOOKUP_DEVICE, dev->vendor_id, dev->device_id);
        strncpy(buffer, namebuf, max_len);
        break;
        }
    }
pci_cleanup(pacc);
return 0;
}




