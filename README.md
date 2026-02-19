# ZIMJI

"Simulateur de Jeu d'Instruction" (Instruction Set Simulator)


## Build instructions:

1. Create a build directory:

        mkdir build && cd build

2. Run CMake to configure the project:

        cmake -S . -B ./build

3. Build the project:

        cmake --build ./build

## Usage

    ./zimji [-v] [-s] [-c] [-f frequency] [-m RAM_size] ROM_file (RAM_file)

* `-v` **Verbose:** Dump CPU status in the console
* `-s` **Step:** Run CPU in instruction-by-instruction mode. If ommited, clock mode is used
* `-c` **Cache** Enable simulated CPU cache
* `-f frequency` **Frequency** Specify the speed of the CPU in clock mode (Hz). Default is 100 Hz. Set to 0 Hz for free running
* `-m RAM_size` **RAM size** Specify the RAM size (data memory) in case no RAM file was given. Default is 32 blocks
* `ROM_File` **Program file** Path to the executable file (PseudoBin format)
* `RAM_File` **RAM file** (*Optional*) Path to data file (PseudoBon format)

## Assembler

An assembler program is provided in the `asm/` folder.