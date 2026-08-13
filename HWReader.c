//Output testing

#include "core.h"
#include "laptop.h"
#include "mainboard.h"
#include "cpu.h"
#include "dram.h"

#include <stdio.h>
#include <string.h>

int main(){
    char test[256];
    int init = get_config_path("TEST_CONFIG",test,sizeof(test));
    if (init>0){
    err_interpretator (init);
    return 1;
    }
    
    char laptop_vendor[64] = "";
    char laptop_model[128] = ""; 

    char mb_name[256] = "";
    char mb_chipset[256] = "";

    char cpu_name[256] = "";
    char cpu_vendor[128] = "";
    char cpu_cores[4] = "";
    char cpu_siblings[4] = "";
    char cpu_L3cache[16] = "";

    int dram_module_count = 0;
    
    init = get_laptop_vendor(laptop_vendor, sizeof(laptop_vendor)) ;
    if (init) err_interpretator(init); 

    init = get_laptop_model(laptop_model, sizeof(laptop_model));
    if (init) err_interpretator(init); 

    init = get_mb_name(mb_name, sizeof(mb_name)); 
    if (init) err_interpretator(init); 
    get_mb_chipset(mb_chipset, sizeof(mb_chipset));

    get_cpu_name(cpu_name, sizeof(cpu_name));
    get_cpu_vendor(cpu_vendor, sizeof(cpu_vendor));
    get_cpu_cores(cpu_cores, sizeof(cpu_cores));
    get_cpu_siblings(cpu_siblings, sizeof(cpu_siblings));
    get_cpu_L3cache(cpu_L3cache, sizeof(cpu_L3cache));

    init = get_module_count(&dram_module_count);
    switch (init)
    {
    case 0:
        break;
    case 501:
        err_interpretator(init);
        break;
    case 502:
        err_interpretator(init);
        break;
    }

    printf("-------------------------------------------------\n");
    printf("|Laptop|\n");
    printf("-------------------------------------------------\n");
    printf("Vendor: %s\n", laptop_vendor);
    printf ("Model: %s\n", laptop_model);

    printf("-------------------------------------------------\n");
    printf("|Мainboard|\n");
    printf("-------------------------------------------------\n");
    printf("Name: %s\n", mb_name);
    printf("Chipset: %s\n", mb_chipset);

    printf("-------------------------------------------------\n");
    printf("|CPU|\n");
    printf("-------------------------------------------------\n");
    printf("Name: %s\n", cpu_name);
    printf("Vendor: %s\n", cpu_vendor);
    printf("Cores: %s\n", cpu_cores);
    printf("Siblings: %s\n", cpu_siblings);
    printf("L3 cache: %s\n", cpu_L3cache);

    printf("-------------------------------------------------\n");
    printf("|DRAM|\n");
    printf("-------------------------------------------------\n");

    if  (dram_module_count>0){
        RamModuleInfo dram[dram_module_count];
        get_dram(dram,dram_module_count);
        for(int i=0; i<dram_module_count; i++){
            printf("DRAM%d\n",i);
            printf("Vendor: %s\n",dram[i].vendor);
            printf("Part number: %s\n",dram[i].part_num);
            printf("Volume: %s\n",dram[i].volume);
            printf("Type: %s\n",dram[i].type);
            printf("Frequency: %s\n",dram[i].freq);
            printf("Rank: %s\n",dram[i].rank);
            printf("-------------------------------------------------\n");
            }
        }
    return 0;
}