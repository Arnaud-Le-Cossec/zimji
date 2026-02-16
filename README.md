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

    ./zimji [-v] [-s] [-f frequency] ROM_file

* `-v` **Verbose:** Dump CPU status in the console
* `-s` **Step:** Run CPU in instruction-by-instruction mode. If ommited, clock mode is used
* `-f frequency` **Frequency** Specify the speed of the CPU in clock mode (Hz). Default is 1 Hz. Set to 0 Hz for free running
* `ROM_File` **Program file** Path to the executable file

## Assembler

An assembler program is provided in the `asm/` folder.