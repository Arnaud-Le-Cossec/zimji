#!/usr/bin/python3

class Cpu:
    def __init__(self, registers_count=32):
        self.pc = 0
        self.instruction = ""
        self.registers_count = registers_count
        self.registers = {}
        self.memory = {}