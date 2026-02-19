#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
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

    unsigned long nb_instr_exec = 0; // Total number of instructions executed
    unsigned long nb_clk_cycl = 0;   // Total number of clock cycles spent

    clock_t run_time, stop_time;

    cpu_t cpu_s;
    cpu_s.data_size = 32; //Default data memory size : 32 blocks
    cpu_s.cache_ena_flag = CPU_CACHE_DISABLED;

   /*Parse command line options*/
    while ((opt = getopt(argc, argv, "vscf:m:")) != -1) {
        switch (opt) {
            case 'v':
                verbose_flag = 1;
                break;
            case 's':
                step_mode = 1;
                break;
            case 'c':
                cpu_s.cache_ena_flag = CPU_CACHE_ENABLED;
                break;
            case 'f':
                clock_frequency = strtol(optarg, NULL, 10);
                if(clock_frequency < 0){
                    fprintf(stderr, "Invalid clock frequency\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case 'm':
                cpu_s.data_size = strtol(optarg, NULL, 10);
                if(cpu_s.data_size <= 0){
                    fprintf(stderr, "Invalid data memory size\n");
                    exit(EXIT_FAILURE);
                }
                break;   
            default:
                fprintf(stderr, "Usage: %s [-v] [-s] [-f frequency] [-m RAM size] ROM_file (RAM_file)\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    
    if (optind >= argc) {
               fprintf(stderr, "Expected ROM file path after options\n");
               exit(EXIT_FAILURE);
    }

    /*Get the number of instructions in ROM file*/
    cpu_s.prog_size = emu_pseudoBin_getSize(argv[optind]);
    if(cpu_s.prog_size == 0){
        fprintf(stderr, "Error reading binary ROM file\n");
        exit(EXIT_FAILURE);
    }

    /*Get the number of instructions in RAM file (if data file given)*/
    if(argc = optind+2){  
        cpu_s.data_size = emu_pseudoBin_getSize(argv[optind+1]);
        if(cpu_s.prog_size == 0){
            fprintf(stderr, "Error reading binary RAM file\n");
            exit(EXIT_FAILURE);
        }
    }

    /*Allocate program memory*/
    cpu_s.prog_mem = (uint32_t*)malloc(cpu_s.prog_size*sizeof(uint32_t));
    if(cpu_s.prog_mem == NULL){
        fprintf(stderr, "Error allocating program memory space\n");
        exit(EXIT_FAILURE);
    }

    /*Allocate data memory*/
    cpu_s.data_mem = (uint32_t*)malloc(cpu_s.data_size*sizeof(uint32_t));
    if(cpu_s.data_mem == NULL){
        fprintf(stderr, "Error allocating data memory space\n");
        exit(EXIT_FAILURE);
    }

    /*Load program into memory*/
    printf("Loaded %zu lines from ROM file %s\n", emu_pseudoBin_load(argv[optind], cpu_s.prog_mem, cpu_s.prog_size), argv[optind]);
    
    /*Load data into memory*/
    if(argc = optind+2){
        printf("Loaded %zu lines from RAM file %s\n", emu_pseudoBin_load(argv[optind+1], cpu_s.data_mem, cpu_s.data_size), argv[optind]);
    }

    /*Reset CPU*/
    cpu_reset(&cpu_s);

    /*Set CPU run flag*/
    cpu_s.run_flag = CPU_STATUS_RUN;
    run_time = clock();

    /*Emulation loop*/
    while(cpu_s.run_flag == CPU_STATUS_RUN){

        nb_clk_cycl += cpu_step(&cpu_s, verbose_flag);

        nb_instr_exec ++;

        if(step_mode){
            /*Start memory monitor. Blocks execution until user input*/
            printf("Press [newline] to execute next instruction. [h] for memory monitor commands \n");
            emu_memMonitor_cli(cpu_s.data_mem, cpu_s.data_size);
        }
        else if(clock_frequency != 0){
            usleep(1000000 / clock_frequency);
        }

    }

    stop_time = clock();

    printf("Executed %ld instructions in %ld clock cycles (%f ms)\n", nb_instr_exec, nb_clk_cycl, ((float)((stop_time-run_time)*1000)/(float)CLOCKS_PER_SEC));

    free(cpu_s.prog_mem);
    free(cpu_s.data_mem);
    return 0;
}