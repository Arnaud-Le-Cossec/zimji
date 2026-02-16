#include "cpu.h"


void _cpu_op_stop  (cpu_t* cpu_s, operand_t* operand_s){
    cpu_s->run_flag = CPU_STATUS_STOP;
}
void _cpu_op_add   (cpu_t* cpu_s, operand_t* operand_s){
    if(operand_s->imm_swt){
        cpu_s->regs[operand_s->dst_reg] = cpu_s->regs[operand_s->src_reg1] + operand_s->imm_val;
    }
    else{
        cpu_s->regs[operand_s->dst_reg] = cpu_s->regs[operand_s->src_reg1] + cpu_s->regs[operand_s->src_reg2];
    }
}
void _cpu_op_sub   (cpu_t* cpu_s, operand_t* operand_s){
    if(operand_s->imm_swt){
        cpu_s->regs[operand_s->dst_reg] = cpu_s->regs[operand_s->src_reg1] - operand_s->imm_val;
    }
    else{
        cpu_s->regs[operand_s->dst_reg] = cpu_s->regs[operand_s->src_reg1] - cpu_s->regs[operand_s->src_reg2];
    }
}
void _cpu_op_mul   (cpu_t* cpu_s, operand_t* operand_s){
    if(operand_s->imm_swt){
        cpu_s->regs[operand_s->dst_reg] = cpu_s->regs[operand_s->src_reg1] * operand_s->imm_val;
    }
    else{
        cpu_s->regs[operand_s->dst_reg] = cpu_s->regs[operand_s->src_reg1] * cpu_s->regs[operand_s->src_reg2];
    } 
}
void _cpu_op_div   (cpu_t* cpu_s, operand_t* operand_s){
    if(operand_s->imm_swt){
        cpu_s->regs[operand_s->dst_reg] = cpu_s->regs[operand_s->src_reg1] / operand_s->imm_val;
    }
    else{
        cpu_s->regs[operand_s->dst_reg] = cpu_s->regs[operand_s->src_reg1] / cpu_s->regs[operand_s->src_reg2];
    } 
}
void _cpu_op_and   (cpu_t* cpu_s, operand_t* operand_s){
    if(operand_s->imm_swt){
        cpu_s->regs[operand_s->dst_reg] = cpu_s->regs[operand_s->src_reg1] & operand_s->imm_val;
    }
    else{
        cpu_s->regs[operand_s->dst_reg] = cpu_s->regs[operand_s->src_reg1] & cpu_s->regs[operand_s->src_reg2];
    } 
}
void _cpu_op_or    (cpu_t* cpu_s, operand_t* operand_s){
    if(operand_s->imm_swt){
        cpu_s->regs[operand_s->dst_reg] = cpu_s->regs[operand_s->src_reg1] | operand_s->imm_val;
    }
    else{
        cpu_s->regs[operand_s->dst_reg] = cpu_s->regs[operand_s->src_reg1] | cpu_s->regs[operand_s->src_reg2];
    } 
}
void _cpu_op_xor   (cpu_t* cpu_s, operand_t* operand_s){
    if(operand_s->imm_swt){
        cpu_s->regs[operand_s->dst_reg] = cpu_s->regs[operand_s->src_reg1] ^ operand_s->imm_val;
    }
    else{
        cpu_s->regs[operand_s->dst_reg] = cpu_s->regs[operand_s->src_reg1] ^ cpu_s->regs[operand_s->src_reg2];
    } 
}
void _cpu_op_shl   (cpu_t* cpu_s, operand_t* operand_s){
    if(operand_s->imm_swt){
        cpu_s->regs[operand_s->dst_reg] = cpu_s->regs[operand_s->src_reg1] << operand_s->imm_val;
    }
    else{
        cpu_s->regs[operand_s->dst_reg] = cpu_s->regs[operand_s->src_reg1] << cpu_s->regs[operand_s->src_reg2];
    } 
}
void _cpu_op_shr   (cpu_t* cpu_s, operand_t* operand_s){
    if(operand_s->imm_swt){
        cpu_s->regs[operand_s->dst_reg] = cpu_s->regs[operand_s->src_reg1] >> operand_s->imm_val;
    }
    else{
        cpu_s->regs[operand_s->dst_reg] = cpu_s->regs[operand_s->src_reg1] >> cpu_s->regs[operand_s->src_reg2];
    } 
}
void _cpu_op_slt   (cpu_t* cpu_s, operand_t* operand_s){
    if(operand_s->imm_swt){
        cpu_s->regs[operand_s->dst_reg] = (cpu_s->regs[operand_s->src_reg1] < operand_s->imm_val)? 1:0;
    }
    else{
        cpu_s->regs[operand_s->dst_reg] = (cpu_s->regs[operand_s->src_reg1] < cpu_s->regs[operand_s->src_reg2])? 1:0;
    } 
}
void _cpu_op_sle   (cpu_t* cpu_s, operand_t* operand_s){
    if(operand_s->imm_swt){
        cpu_s->regs[operand_s->dst_reg] = (cpu_s->regs[operand_s->src_reg1] <= operand_s->imm_val)? 1:0;
    }
    else{
        cpu_s->regs[operand_s->dst_reg] = (cpu_s->regs[operand_s->src_reg1] <= cpu_s->regs[operand_s->src_reg2])? 1:0;
    } 
}
void _cpu_op_seq   (cpu_t* cpu_s, operand_t* operand_s){
    if(operand_s->imm_swt){
        cpu_s->regs[operand_s->dst_reg] = (cpu_s->regs[operand_s->src_reg1] == operand_s->imm_val);
    }
    else{
        cpu_s->regs[operand_s->dst_reg] = (cpu_s->regs[operand_s->src_reg1] == cpu_s->regs[operand_s->src_reg2]);
    } 
}
void _cpu_op_load(cpu_t* cpu_s, operand_t* operand_s){
    cpu_s->regs[operand_s->dst_reg] = cpu_s->data_mem[cpu_s->regs[operand_s->src_reg1]+operand_s->imm_val];
}
void _cpu_op_store(cpu_t* cpu_s, operand_t* operand_s){
    cpu_s->data_mem[cpu_s->regs[operand_s->src_reg1]+operand_s->imm_val] = cpu_s->regs[operand_s->dst_reg];
}
void _cpu_op_jmp(cpu_t* cpu_s, operand_t* operand_s){
    if(operand_s->imm_swt){
        cpu_s->regs[operand_s->src_reg1] = cpu_s->pc;
        cpu_s->pc = operand_s->imm_val;
    }
    else{
        cpu_s->regs[operand_s->src_reg1] = cpu_s->pc;
        cpu_s->pc = cpu_s->regs[operand_s->dst_reg];
    } 
}
void _cpu_op_braz  (cpu_t* cpu_s, operand_t* operand_s){
    if(cpu_s->regs[operand_s->src_reg1] == 0){
        cpu_s->pc = operand_s->imm_val;
    }
}
void _cpu_op_brazn (cpu_t* cpu_s, operand_t* operand_s){
    if(cpu_s->regs[operand_s->src_reg1] != 0){
        cpu_s->pc = operand_s->imm_val;
    }
}
void _cpu_op_scall (cpu_t* cpu_s, operand_t* operand_s){
    switch (operand_s->imm_val)
    {
    case 0:
        /* code */
        printf("[SCALL] Enter a number:\n");
        scanf("%d", &cpu_s->regs[1]);
        break;
    case 1:
        printf("[SCALL] R1 value: %d (0x%.8x)\n", cpu_s->regs[1], cpu_s->regs[1]);
        break;
    case 3:
        printf("[SCALL] R1 value (char): %c\n", (char)cpu_s->regs[1]);
        break;
    case 4:
        printf("[SCALL] String at &R1: %s\n", &(cpu_s->data_mem[cpu_s->regs[1]]));
        break;
    default:
        printf("[SCALL] Unknown SCALL function\n");
        break;
    }
}

/******************************************************************************
 * CPU cycles
 *****************************************************************************/

void _cpu_fetch(cpu_t* cpu_s){
    cpu_s->ir = cpu_s->prog_mem[cpu_s->pc++];
}

void _cpu_decode(cpu_t* cpu_s, operand_t* operand_s){
    operand_s->opcode = (int)((cpu_s->ir >> 27) & 0x1F);
    operand_s->type = decoding_type[operand_s->opcode];
    switch (operand_s->type)
    {
    case TYP0:
        operand_s->src_reg1 = (int)((cpu_s->ir >> 22) & 0x1F);
        operand_s->imm_swt = (int)((cpu_s->ir >> 21) & 0x1);
        if(operand_s->imm_swt){
            operand_s->imm_val = (int)((cpu_s->ir >> 5) & 0xFFFF);
        }
        else{
            operand_s->src_reg2 = (int)((cpu_s->ir >> 5) & 0x1F);
        }
        operand_s->dst_reg = (int)(cpu_s->ir & 0x1F);
        break;
    case TYP1:
        operand_s->imm_swt = (int)((cpu_s->ir >> 26) & 0x1);
        if(operand_s->imm_swt){
            operand_s->imm_val = (int)((cpu_s->ir >> 5) & 0xFFFF);
        }
        else{
            operand_s->dst_reg = (int)((cpu_s->ir >> 5) & 0x1F);
        }
        operand_s->src_reg1 = (int)(cpu_s->ir & 0x1F);
        break;
    case TYP2:
        operand_s->src_reg1 = (int)((cpu_s->ir >> 22) & 0x1F);
        operand_s->imm_val = (int)(cpu_s->ir & 0x3FFFFF);
        break;
    case TYP3:
        operand_s->imm_val = (int)(cpu_s->ir & 0x7FFFFFF);
        break;
    case TYP4:
        /*Fall back to default*/
    default:
        break;
    }
}

void _cpu_execute(cpu_t* cpu_s, operand_t* operand_s){
    instruction_set[operand_s->opcode](cpu_s, operand_s);
}

void cpu_step(cpu_t* cpu_s, int verbose_flag){

    operand_t operand_s;

    if(verbose_flag){
        printf("PC:%d ", cpu_s->pc);
    }

    _cpu_fetch(cpu_s);

    _cpu_decode(cpu_s, &operand_s);

    if(verbose_flag){
        switch (operand_s.type)
        {
        case TYP0:
            if(operand_s.imm_swt){
                printf("Instr: %s r%d, %d, r%d\n", 
                    mnemonics[operand_s.opcode], 
                    operand_s.src_reg1, 
                    operand_s.imm_val, 
                    operand_s.dst_reg
                );
            }
            else{
                printf("Instr: %s r%d, r%d, r%d\n", 
                    mnemonics[operand_s.opcode], 
                    operand_s.src_reg1, 
                    operand_s.src_reg2, 
                    operand_s.dst_reg
                );
            }
            break;
        case TYP1:
            if(operand_s.imm_swt){
                printf("Instr: %s %d, r%d\n", 
                    mnemonics[operand_s.opcode], 
                    operand_s.imm_val, 
                    operand_s.src_reg1
                );
            }
            else{
                printf("Instr: %s %d, r%d\n", 
                    mnemonics[operand_s.opcode], 
                    operand_s.dst_reg, 
                    operand_s.src_reg1
                );
            }
            break;
        case TYP2:
            printf("Instr: %s r%d, %d\n", 
                mnemonics[operand_s.opcode], 
                operand_s.src_reg1, 
                operand_s.imm_val
            );
            break;
        case TYP3:
            printf("Instr: %s %d\n", 
                mnemonics[operand_s.opcode], 
                operand_s.imm_val
            );
            break;
        case TYP4:
            printf("Instr: %s\n", 
                mnemonics[operand_s.opcode]
            );
        default:
            break;
        }
    }

    _cpu_execute(cpu_s, &operand_s);   

    if(verbose_flag){
        for(int i=0; i<CPU_REG_COUNT; i++){
            printf("r%.2d=0x%.8x\t",i, cpu_s->regs[i]);
            if((i % (CPU_REG_COUNT/4)) == (CPU_REG_COUNT/4)-1){
                printf("\n");
            }
        }
    }

    /*Force register 0 to 0*/
    cpu_s->regs[0] = 0;
}

void cpu_reset(cpu_t* cpu_s){
    cpu_s->run_flag = CPU_STATUS_STOP;
    cpu_s->pc = 0U;
    cpu_s->ir = 0U;
    for(int i=0; i<CPU_REG_COUNT; i++){
        cpu_s->regs[i] = 0U;
    }
}