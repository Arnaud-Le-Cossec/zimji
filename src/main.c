#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "cpu.h"
#include "emulator_utility.h"




/******************************************************************************
 * Main
 *****************************************************************************/

int main(int argc,char ** argv) {
    int opt;
    int verbose_flag = 0;
    int step_mode = 0;
    int clock_frequency = 1; //Default 1Hz

    cpu_t cpu_s;
    operand_t operand_s;

   /*Parse command line options*/
    while ((opt = getopt(argc, argv, "vsf:")) != -1) {
        switch (opt) {
            case 'v':
                verbose_flag = 1;
                break;
            case 's':
                step_mode = 1;
                break;
            case 'f':
                clock_frequency = strtol(optarg, NULL, 10);
                if(clock_frequency <= 0){
                    fprintf(stderr, "Invalid clock frequency\n");
                    exit(EXIT_FAILURE);
                }
                break;
            default:
                fprintf(stderr, "Usage: %s [-v] [-s] [-f frequency] ROM_file\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    
    if (optind >= argc) {
               fprintf(stderr, "Expected ROM file path after options\n");
               exit(EXIT_FAILURE);
    }
    
    printf("ROM file path argument = %s\n", argv[optind]);

    /*Get the number of instructions in ROM file*/
    cpu_s.prog_size = emu_pseudoBin_getSize(argv[optind]);
    if(cpu_s.prog_size == 0){
        fprintf(stderr, "Error reading binary file\n");
        exit(EXIT_FAILURE);
    }
    printf("%d\n",cpu_s.prog_size);

    /*Allocate memory*/
    cpu_s.prog_mem = (uint32_t*)malloc(cpu_s.prog_size*sizeof(uint32_t));
    if(cpu_s.prog_mem == NULL){
        fprintf(stderr, "Error allocating program memory space\n");
        exit(EXIT_FAILURE);
    }

    /*Load program into memory*/
    printf("Loaded %zu lines from file %s\n", emu_pseudoBin_Load(argv[optind], cpu_s.prog_mem, cpu_s.prog_size), argv[optind]);
    
    cpu_reset(&cpu_s);

    cpu_s.run_flag = CPU_STATUS_RUN;

    /*Emulation loop*/
    while(cpu_s.run_flag == CPU_STATUS_RUN){

        //cpu_step(&cpu_s);

        if(verbose_flag){
            printf("PC:%d ", cpu_s.pc);
        }

        _cpu_fetch(&cpu_s);

        _cpu_decode(&cpu_s, &operand_s);

        if(verbose_flag){
            printf("Instr: %s s1=%d, s2=%d, imm?=%d, imm=%d, dst=%d\n", 
                mnemonics[operand_s.opcode], 
                operand_s.src_reg1, 
                operand_s.src_reg2, 
                operand_s.imm_swt, 
                operand_s.imm_val, 
                operand_s.dst_reg
            );
        }

        _cpu_execute(&cpu_s, &operand_s);   

        if(verbose_flag){
            //cdump cpu state
            for(int i=0; i<CPU_REG_COUNT; i++){
                printf("r%d=%d ",i, cpu_s.regs[i]);
            }
            printf("\n");
            
        }

        if(step_mode){
            printf("Press ENTER to execute next instruction...\n");
            getchar();
        }
        else{
            usleep(1000000 / clock_frequency);
        }


    }
    free(cpu_s.prog_mem);
    return 0;
}