
#ifndef ZIMJI_CORE_H_INCLUDED
#define ZIMJI_CORE_H_INCLUDED

#include <stdint.h>
#include <stdio.h>

#define CPU_REG_COUNT 32

#define CPU_CACHE_DISABLED 0
#define CPU_CACHE_ENABLED 1
#define CPU_CACHE_MISS 0
#define CPU_CACHE_HIT 1
#define CPU_CACHE_BLOCK_INVALID 0
#define CPU_CACHE_BLOCK_VALID 1
#define CPU_CACHE_BLOCK_COUNT 4 /*Must be a power of 2 and > 0!*/
#define CPU_CACHE_BLOCK_SIZE 8  /*Must be a power of 2 and > 0!*/
#define CPU_CACHE_ADDRSLICE_DATA_BIT 0
#define CPU_CACHE_ADDRSLICE_BLOCK_BIT (CPU_CACHE_ADDRSLICE_DATA_BIT + __builtin_ctzl(CPU_CACHE_BLOCK_SIZE)) //3
#define CPU_CACHE_ADDRSLICE_TAG_BIT (CPU_CACHE_ADDRSLICE_BLOCK_BIT + __builtin_ctzl(CPU_CACHE_BLOCK_COUNT)) //5

#define CPU_STATUS_STOP 0
#define CPU_STATUS_RUN 1

#define CPU_CLKCYCL_ALU_OP 1
#define CPU_CLKCYCL_TEST 1
#define CPU_CLKCYCL_RAM_ACS 3
#define CPU_CLKCYCL_CACHE_ACS 2
#define CPU_CLKCYCL_JMP 1
#define CPU_CLKCYCL_BRANCH_PASS 1
#define CPU_CLKCYCL_BRANCH_JMP 2
#define CPU_CLKCYCL_SCALL 5

/*Cache block structure*/
typedef struct
{
    int valid_flag;
    uint32_t tag;
    uint32_t data[CPU_CACHE_BLOCK_SIZE];
} cache_t;

/*CPU data structure*/
typedef struct
{   
    int run_flag;                           /*CPU Run flag = CPU_STATUS_STOP | CPU_STATUS_RUN*/
    int cache_ena_flag;                     /*CPU Cache enable flag = CPU_CACHE_DISABLED | CPU_CACHE_ENABLED*/

    uint32_t pc;                            /*Program counter*/
    uint32_t ir;                            /*Instruction register*/
    uint32_t regs[CPU_REG_COUNT];           /*Registers*/
    cache_t cache_s[CPU_CACHE_BLOCK_COUNT]; /*Cache*/

    uint32_t *prog_mem;                     /*Program memory space*/
    uint32_t *data_mem;                     /*Data memory space*/
    size_t   prog_size;                     /*Program memory size*/
    size_t   data_size;                     /*Data memory size*/
} cpu_t;

/*Enumeration for decoding type*/
enum decode_type_e
{
    TYP0,
    TYP1,
    TYP2,
    TYP3,
    TYP4
};

/*Instruction operand structure*/
typedef struct
{
    enum decode_type_e type;
    int opcode;
    int src_reg1;
    int src_reg2;
    int imm_swt;
    int imm_val;
    int dst_reg;
} operand_t;

/*Instruction set*/
int _cpu_op_stop  (cpu_t* cpu_s, operand_t* operand_s);
int _cpu_op_add   (cpu_t* cpu_s, operand_t* operand_s);
int _cpu_op_sub   (cpu_t* cpu_s, operand_t* operand_s);
int _cpu_op_mul   (cpu_t* cpu_s, operand_t* operand_s);
int _cpu_op_div   (cpu_t* cpu_s, operand_t* operand_s);
int _cpu_op_and   (cpu_t* cpu_s, operand_t* operand_s);
int _cpu_op_or    (cpu_t* cpu_s, operand_t* operand_s);
int _cpu_op_xor   (cpu_t* cpu_s, operand_t* operand_s);
int _cpu_op_shl   (cpu_t* cpu_s, operand_t* operand_s);
int _cpu_op_shr   (cpu_t* cpu_s, operand_t* operand_s);
int _cpu_op_slt   (cpu_t* cpu_s, operand_t* operand_s);
int _cpu_op_sle   (cpu_t* cpu_s, operand_t* operand_s);
int _cpu_op_seq   (cpu_t* cpu_s, operand_t* operand_s);
int _cpu_op_load  (cpu_t* cpu_s, operand_t* operand_s);
int _cpu_op_store (cpu_t* cpu_s, operand_t* operand_s);
int _cpu_op_jmp   (cpu_t* cpu_s, operand_t* operand_s);
int _cpu_op_braz  (cpu_t* cpu_s, operand_t* operand_s);
int _cpu_op_brazn (cpu_t* cpu_s, operand_t* operand_s);
int _cpu_op_scall (cpu_t* cpu_s, operand_t* operand_s);

/*Instruction table*/
typedef int (*instruction_t)(cpu_t* cpu_s, operand_t* operand_s);

static const instruction_t instruction_set[19] = {
    _cpu_op_stop ,
    _cpu_op_add  ,
    _cpu_op_sub  ,
    _cpu_op_mul  ,
    _cpu_op_div  ,
    _cpu_op_and  ,
    _cpu_op_or   ,
    _cpu_op_xor  ,
    _cpu_op_shl  ,
    _cpu_op_shr  ,
    _cpu_op_slt  ,
    _cpu_op_sle  ,
    _cpu_op_seq  ,
    _cpu_op_load ,
    _cpu_op_store,
    _cpu_op_jmp  ,
    _cpu_op_braz ,
    _cpu_op_brazn,
    _cpu_op_scall,
};

/*Decoding types*/
static const enum decode_type_e decoding_type[19] = {
    TYP4,
    TYP0,
    TYP0,
    TYP0,
    TYP0,
    TYP0,
    TYP0, 
    TYP0,
    TYP0,
    TYP0,
    TYP0,
    TYP0,
    TYP0,
    TYP0,
    TYP0,
    TYP1,
    TYP2,
    TYP2,
    TYP3,
};

static const char* mnemonics[19] = {
    "STOP" ,
    "ADD"  ,
    "SUB"  ,
    "MUL"  ,
    "DIV"  ,
    "AND"  ,
    "OR"   , 
    "XOR"  ,
    "SHL"  ,
    "SHR"  ,
    "SLT"  ,
    "SLE"  ,
    "SEQ"  ,
    "LOAD" ,
    "STORE",
    "JMP"  ,
    "BRAZ" ,
    "BRANZ",
    "SCALL"
};

/******************************************************************************
 * Cache
 *****************************************************************************/

/**
 * @brief Init cache by clearing valid_flag
 * @param cpu_s CPU structure pointer
 * @returns None
 */
void _cpu_cache_init(cpu_t* cpu_s);

/**
 * @brief Check if address is in cache
 * @param cpu_s CPU structure pointer
 * @param address address tp check
 * @returns 0=Cache miss, 1=In Cache
 */
int _cpu_cache_read(cpu_t* cpu_s, uint32_t address, uint32_t* data);

void _cpu_cache_write(cpu_t* cpu_s, uint32_t address);

/******************************************************************************
 * CPU cycles
 *****************************************************************************/

/**
 * @brief Get instruction from program memory (Prog_mem) into instruction register (IR) and increment program counter (PC)
 * @param cpu_s CPU structure pointer
 * @returns None
 */
void _cpu_fetch(cpu_t* cpu_s);

/**
 * @brief Decodes instruction in instruction register (IR) and extract the operands
 * @param cpu_s CPU structure pointer
 * @param operand_s Operand structure pointer
 * @returns None
 */
void _cpu_decode(cpu_t* cpu_s, operand_t* operand_s);

/**
 * @brief Execute the instruction form the operand
 * @param cpu_s CPU structure pointer
 * @param operand_s Operand structure pointer
 * @returns Simulated clock cycles to complete instruction
 */
int _cpu_execute(cpu_t* cpu_s, operand_t* operand_s);


/******************************************************************************
 * Public functions
 *****************************************************************************/

/**
 * @brief Fetch, decode and execute instruction
 * @param cpu_s CPU structure pointer
 * @param verbose_flag Set to one to enable verbose mode
 * @returns Simulated clock cycles to complete instruction
 */
int cpu_step(cpu_t* cpu_s, int verbose_flag);

/**
 * @brief Reset CPU to initial state
 * @param cpu_s CPU structure pointer
 * @returns None
 */
void cpu_reset(cpu_t* cpu_s);



#endif // ZIMJI_CORE_H_INCLUDED