# ZIMJI TEST PROGRAMS

This folder contains projects to test the assembler, simulator and help you get started.

## Structure 

Each test will contain the following elements:

- **README file**
- **Assembly source code** `*.asm`
- **Pre-compiled binary program** ([PseudoBin format](../ASSEMBLER/README.md#pseudobin-format)) `.bin`
- **Pre-compiled binary data** ([PseudoBin format](../ASSEMBLER/README.md#pseudobin-format)) `data.bin` *(Optional)*

## Run a test

To run the test `X` from the `TEST/X` folder:

    ./../../ISS/src/zimji -s -v X.bin 

If there is a data file:

    ./../../ISS/src/zimji -s -v X.bin X_data.bin

To know more, see the [simulator documentation](../ISS/README.md)

## Compile a test

To compile the test `X` from the `TEST/X` folder:

    ./../../ASSEMBLER/zimji_asm X.asm X.bin

> Data binary need to be created seperarately

To know more, see the [assembler documentation](../ASSEMBLER/README.md)

## Available tests 

This repository contains: 

- [**Memory test**](mem_test/mem.asm) Copies a string in memory from one address to another, then check data integrity. *Excellent to test the cpu cache!*
- [**Speed test**](speed_test/speed.asm) Run a big loop to test simulator speed
- [**PGCD**](pgcd/README.md) Calculates the greatest common divider
- [**Chenillard**](chenillard/README.md) Rotate a string in memory
- [**Adventure**](adventure/README.md) Small text-based adventure game


## Licence

Copyright © 2026 Arnaud LE COSSEC

This project falls under the MIT licence. See [licence file](../LICENCE.md).