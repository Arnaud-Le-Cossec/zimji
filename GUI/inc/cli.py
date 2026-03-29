#!/usr/bin/python3

import re

class Cli:
    def __init__(self):
        pass

    def decode(self, console_output):
        # Extract PC
        pc_match = re.search(r"PC:(\d+)", console_output)
        pc_val = pc_match.group(1) if pc_match else "Not found"

        # Extract Instruction (until the end line)
        instr_match = re.search(r"Instr:\s*(.*)", console_output)
        instr_val = instr_match.group(1).strip() if instr_match else "Not found"

        # Extract Registers (rXX=0xXXXXXXXX)
        # findall returns a list of tuples like [('r00', '0x00000000'), ...]
        reg_matches = re.findall(r"(r\d{2})=(0x[0-9a-fA-F]+)", console_output)
        registers = {reg: val for reg, val in reg_matches}

        return pc_val, instr_val, registers