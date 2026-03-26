# ZIMJI

"Simulateur de Jeu d'Instruction" (Instruction Set Simulator)

## Build simulator:

1. Create a build directory:

        mkdir build && cd build

2. Run CMake to configure the project:

        cmake -S . -B ./build

3. Build the project:

        cmake --build ./build

## Usage

    ./zimji [-v] [-s] [-c] [-f frequency] [-m RAM_size] ROM_file (RAM_file)

* `-v` **Verbose:** Dump CPU status in the console
* `-s` **Step:** Run CPU in step mode, waiting user input between each instruction. If ommited, clock mode is used
* `-c` **Cache** Enable simulated CPU cache
* `-f frequency` **Frequency** Specify the speed of the CPU in clock mode (Hz). Default is 100 Hz. Set to 0 Hz for free running
* `-m RAM_size` **RAM size** Specify the RAM size (data memory) in case no RAM file was given. Default is 32 blocks
* `ROM_File` **Program file** Path to the executable file (PseudoBin format)
* `RAM_File` **RAM file** (*Optional*) Path to data file (PseudoBon format)

## Example:

Example command in **Step Mode** and **Verbose**:

        ./build/src/zimji -v -s TEST/mem_test/mem.bin TEST/mem_test/data.bin

## Memory Monitor (Step mode)

This ISS features a memory monitor. It allows user to inspect and modify data memory while the simulator is running.

>**NOTE:** The memory monitor is only available in **step mode `-s`**.

In **step mode**, at the end of each instruction, the ISS will prompt the user with `>>>`. From there you can type commands. If you hit `enter` without any commands, you will simply step to the next instruction.

- `[newline]` Next instruction
- `R address` **Read** one word from memory at *address* (**HEXADECIMAL**)
- `R address size` **Read** *size* (**DECIMAL**) words from memory starting at *address* (**HEXADECIMAL**)
- `W address=value` **Write** the word *value* (**HEXADECIMAL**) into memory at *address* (**HEXADECIMAL**)
- `H` Show **help**

# Instruction set

See [instruction set](../ASSEMBLER/README.md)