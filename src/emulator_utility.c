#include "emulator_utility.h"


size_t emu_pseudoBin_getSize(char* filename){
    size_t line_count = 0;
    char line_buffer[EMU_LINE_BUFFER_SIZE];
    size_t address = 0;
    size_t max_address = 0;

    FILE *file = fopen(filename, "r");
    if(file == NULL){
        printf("Could not open file %s\n", filename);
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

size_t emu_pseudoBin_load(char* filename, uint32_t* memory_ptr, size_t memory_size){
    size_t line_count = 0;
    char line_buffer[EMU_LINE_BUFFER_SIZE];
    char* data_ptr = NULL;
    uint32_t address = 0;
    uint32_t data = 0;

    FILE *file = fopen(filename, "r");
    if(file == NULL){
        printf("Could not open file %s\n", filename);
        return 0;
    }

    while (fgets(line_buffer, EMU_LINE_BUFFER_SIZE, file)){
        
        address = (uint32_t)strtol(line_buffer, &data_ptr, 16);
        data = (uint32_t)strtol(data_ptr, NULL, 16);

        //printf("%.8x %.8x\n", address, data);
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

void emu_memMonitor_cli(uint32_t* memory_ptr, size_t memory_size){
    char buffer[EMU_LINE_BUFFER_SIZE];
    char *buffer_idx_ptr, *buffer_end_ptr;
    char cmd=' ';
    uint32_t addr=0;
    uint32_t val=0;
    
    while (1)
    {
        printf("\n>>> ");
        if(fgets(buffer, sizeof(buffer), stdin) == NULL){
            /*EOF or error*/
            break;
        }
        
        /*Init index pointer to the start of buffer*/
        buffer_idx_ptr = buffer;

        /*Skip whitespace*/
        while(isspace(*buffer_idx_ptr)) buffer_idx_ptr++;

        /*Check for empty line*/
        if(*buffer_idx_ptr == '\0'){
            break;
        }

        /*Get command character*/
        char cmd = *buffer_idx_ptr++;

        /*Quit command*/
        if(cmd == 'Q' || cmd == 'q'){
            break;
        }

        /*Help command*/
        if(cmd == 'H' || cmd == 'h'){
            printf("Commands:\n - Exit/Next \t:=\tQ|[newline]\n - Read \t:=\tR <address(hex)>(,<page size(dec)>)\n - Write \t:=\tW <address(hex)>=<value(hex)>\n - Show help \t:=\tH");
            continue;
        }

        /*Read command*/
        else if(cmd == 'R' || cmd == 'r'){

            /*Get address*/

            addr = (uint32_t)strtol(buffer_idx_ptr, &buffer_end_ptr, 16);
            if(buffer_idx_ptr == buffer_end_ptr){
                printf("Syntax Error ! Read: R <address(hex)>\n");
                continue;
            } 
            if(addr < 0 || addr >= memory_size){
                printf("Invalid address ! Range: 0x0 - 0x%x)\n", memory_size-1);
                continue;
            }

            /*Here 'val' is used to set page_size*/
            val = EMU_MEMMON_PAGESIZE_DEFAULT;

            /*Get optional ',' character*/

            buffer_idx_ptr=buffer_end_ptr;
            /*Skip whitespace*/
            while(isspace(*buffer_idx_ptr)) buffer_idx_ptr++;
            /*Check ',' presence*/
            if(*buffer_idx_ptr == ','){
                buffer_idx_ptr++;
                val = (uint32_t)strtol(buffer_idx_ptr, &buffer_end_ptr, 10);
                if(buffer_idx_ptr == buffer_end_ptr ){
                    printf("Syntax Error ! Read := R <address(hex)>(,<page size(dec)>)\n");
                    continue;
                }
                if(val < 0){
                    printf("Invalid page size ! Range: > 0\n");
                    continue;
                }
            }

            /*Read*/

            emu_memMonitor_page(memory_ptr, memory_size, addr, val);
        }

        /*Write command*/
        else if(cmd == 'W' || cmd == 'w'){

            /*Get address*/

            addr = (uint32_t)strtol(buffer_idx_ptr, &buffer_end_ptr, 16);
            if(buffer_idx_ptr == buffer_end_ptr){
                printf("Syntax Error ! Write: W <address(hex)>=<value(hex)>\n");
                continue;
            }
            if(addr < 0 || addr >= memory_size){
                printf("Invalid address ! Range: 0x0 - 0x%x)\n", memory_size-1);
                continue;
            }

            /*Get '=' character*/

            buffer_idx_ptr=buffer_end_ptr;
            /*Skip whitespace*/
            while(isspace(*buffer_idx_ptr)) buffer_idx_ptr++;
            /*Check '=' presence*/
            if(*buffer_idx_ptr != '='){
                printf("Syntax Error ! Write: W <address(hex)>=<value(hex)>\n");
                continue;
            }

            /*Get value to be written*/

            buffer_idx_ptr++;
            val = (uint32_t)strtol(buffer_idx_ptr, &buffer_end_ptr, 16);
            if(buffer_idx_ptr == buffer_end_ptr){
                printf("Syntax Error ! Write: W <address(hex)>=<value(hex)>3\n");
                continue;
            }
        
            /*Write*/

            memory_ptr[(size_t)addr] = (uint32_t)val;
        }
        else{
            printf("Unknown command '%c'\n", cmd);
        }
    }
}

void emu_memMonitor_page(uint32_t* memory_ptr, size_t memory_size, uint32_t start_addr, uint32_t page_size){
    // ugly code...
    char ascii[9];
    uint32_t tmp;
    uint32_t offset;
    for(offset = 0; offset < page_size; offset++){
        /*Check memor*/
        if(start_addr + offset >= memory_size){

            break;
        }
        /*Print address at line start*/
        if(offset % 8 == 0){
            printf("%08X: ", start_addr + offset);
        }
        /*Print memory content*/
        tmp = memory_ptr[start_addr + offset];
        printf("%08X ", tmp);
        /*ASCII representation*/
        ascii[offset % 8] = isprint(tmp) ? (char)tmp : '.';
        if(offset % 8 == 7){
            ascii[8] = '\0';
            printf("%s\n", ascii);
        }
    }
    if(offset >= page_size){
        ascii[offset%8] = '\0';
        printf("%s\n", ascii);
    }
}