#include "emulator_utility.h"


size_t emu_pseudoBin_getSize(char* filename){
    size_t line_count = 0;
    char line_buffer[EMU_LINE_BUFFER_SIZE];
    size_t address = 0;
    size_t max_address = 0;

    FILE *file = fopen(filename, "r");
    if(file == NULL){
        printf("Could not open file %s\n", filename);
        fclose(file);
        return 0;
    }

    while (fgets(line_buffer, EMU_LINE_BUFFER_SIZE, file)){
        
        address = (size_t)strtol(line_buffer, NULL, 16);
        if(address > max_address){
            max_address = address;
        }
        
    }

    if(ferror(file) != 0){
        printf("Error reading file %s\n", filename);
        fclose(file);
        return 0;
    }
    
    fclose(file);
    return max_address+1;
}

size_t emu_pseudoBin_Load(char* filename, uint32_t* memory_ptr, size_t memory_size){
    size_t line_count = 0;
    char line_buffer[EMU_LINE_BUFFER_SIZE];
    char* data_ptr = NULL;
    uint32_t address = 0;
    uint32_t data = 0;

    FILE *file = fopen(filename, "r");
    if(file == NULL){
        printf("Could not open file %s\n", filename);
        fclose(file);
        return 0;
    }

    while (fgets(line_buffer, EMU_LINE_BUFFER_SIZE, file)){
        
        address = (uint32_t)strtol(line_buffer, &data_ptr, 16);
        data = (uint32_t)strtol(data_ptr, NULL, 16);

        printf("%.8x %.8x\n", address, data);
        memory_ptr[address] = data;
        line_count ++;
    }

    if(ferror(file) != 0){
        printf("Error reading file %s\n", filename);
        fclose(file);
        return 0;
    }
    
    fclose(file);
    return line_count;
}
