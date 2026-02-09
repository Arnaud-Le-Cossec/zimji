
#ifndef ZIMJI_CORE_H_INCLUDED
#define ZIMJI_CORE_H_INCLUDED

#include <stdint.h>
#include <stdio.h>

#define CPU_REG_COUNT 32

#define CPU_STATUS_STOP 0
#define CPU_STATUS_RUN 1

/*CPU data structure*/
typedef struct
{   
    int run_flag;
    uint32_t pc;                    /*Program counter*/
    uint32_t ir;                    /*Instruction register*/
    uint32_t regs[CPU_REG_COUNT];   /*Registers*/
    uint32_t *prog_mem;             /*Program memory space*/
    uint32_t *data_mem;             /*Data memory space*/
    size_t   prog_size;             /*Program memory size*/
    size_t   data_size;             /*Data memory size*/
} cpu_t;

typedef struct
{
    int opcode;
    int src_reg1;
    int src_reg2;
    int imm_swt;
    int imm_val;
    int dst_reg;
} operand_t;

enum decode_type_e
{
    TYP0,
    TYP1,
    TYP2,
    TYP3,
    TYP4
};

/*Instruction set*/
void _cpu_op_stop  (cpu_t* cpu_s, operand_t* operand_s);
void _cpu_op_add   (cpu_t* cpu_s, operand_t* operand_s);
void _cpu_op_sub   (cpu_t* cpu_s, operand_t* operand_s);
void _cpu_op_mul   (cpu_t* cpu_s, operand_t* operand_s);
void _cpu_op_div   (cpu_t* cpu_s, operand_t* operand_s);
void _cpu_op_and   (cpu_t* cpu_s, operand_t* operand_s);
void _cpu_op_or    (cpu_t* cpu_s, operand_t* operand_s);
void _cpu_op_xor   (cpu_t* cpu_s, operand_t* operand_s);
void _cpu_op_shl   (cpu_t* cpu_s, operand_t* operand_s);
void _cpu_op_shr   (cpu_t* cpu_s, operand_t* operand_s);
void _cpu_op_slt   (cpu_t* cpu_s, operand_t* operand_s);
void _cpu_op_sle   (cpu_t* cpu_s, operand_t* operand_s);
void _cpu_op_seq   (cpu_t* cpu_s, operand_t* operand_s);
void _cpu_op_load  (cpu_t* cpu_s, operand_t* operand_s);
void _cpu_op_store (cpu_t* cpu_s, operand_t* operand_s);
void _cpu_op_jmp   (cpu_t* cpu_s, operand_t* operand_s);
void _cpu_op_braz  (cpu_t* cpu_s, operand_t* operand_s);
void _cpu_op_brazn (cpu_t* cpu_s, operand_t* operand_s);
void _cpu_op_scall (cpu_t* cpu_s, operand_t* operand_s);

/*Instruction table*/
typedef void (*instruction_t)(cpu_t* cpu_s, operand_t* operand_s);

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

void _cpu_fetch(cpu_t* cpu_s);

void _cpu_decode(cpu_t* cpu_s, operand_t* operand_s);

void _cpu_execute(cpu_t* cpu_s, operand_t* operand_s);

void cpu_step(cpu_t* cpu_s, int verbose_flag);

void cpu_reset(cpu_t* cpu_s);



#endif // ZIMJI_CORE_H_INCLUDED