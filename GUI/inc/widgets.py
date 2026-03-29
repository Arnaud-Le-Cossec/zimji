#!/usr/bin/python3

import tkinter as tk
from inc.cpu import Cpu

class Widget_CPU_Status(tk.Widget):
    def __init__(self, master):
        self.master = master
        self.master.title("Zimji CPU Debugger")
        self.cpu_data = Cpu()

        # Create UI elements
        self.create_widgets()

    def create_widgets(self):
        # PC Label
        self.pc_label = tk.Label(self.master, text="Program Counter: ")
        self.pc_label.grid(row=0, column=0, sticky="w")

        # Instruction Label
        self.instr_label = tk.Label(self.master, text="Instruction: ")
        self.instr_label.grid(row=1, column=0, sticky="w")


    def update_cpu_data(self, cpu_data: Cpu):
        self.cpu_data.pc = cpu_data.pc
        self.cpu_data.instruction = cpu_data.instruction
        self.cpu_data.registers = cpu_data.registers

        # Update UI
        self.pc_label.config(text=f"Program Counter: {self.cpu_data.pc}")
        self.instr_label.config(text=f"Instruction: {self.cpu_data.instruction}")