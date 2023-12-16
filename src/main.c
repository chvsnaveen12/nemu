#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "common.h"

void mem_fetch(system cpu, uint32_t addr, uint32_t *value){

}

uint64_t get_file_size(char *file_name){
    FILE *p_file = fopen(file_name, "rb");

    if(p_file == NULL)
        die_msg("Couldn't open file");
    
    fseek(p_file, 0, SEEK_END);
    uint64_t lsize = ftell(p_file);
    
    fclose(p_file);
    
    return lsize;
}

uint64_t write_mem_from_file(char *file_name, uint8_t *memory, uint64_t mem_size){
    FILE *p_file = fopen(file_name, "rb");
    
    if(p_file == NULL)
        die_msg("Couldn't open file");
    
    uint64_t lsize = get_file_size(file_name);

    if(lsize > mem_size)
        die_msg("File bigger than mem");
    
    uint64_t result = fread(memory, sizeof(uint8_t), lsize, p_file);
    if(result != lsize)
        die_msg("Error while reading");

    fclose(p_file);
    return lsize;
}

int main (int argc, char *argv[]){
    if(argc != 3)
        die_msg("Wrong number of params, usage ./emulator kernel_file dtb_file");
    
    char *kernel_file = argv[1];
    char *dtb_file = argv[2];

    system cpu;
    memset(&cpu, 0, sizeof(cpu));

    core core0 = {
        .priv = &cpu,
        .mem_fetch = mem_fetch;
        .mem_load = mem_load;
        .mem_store = mem_store;
    }

    cpu.ram = malloc();

    return 0;
}