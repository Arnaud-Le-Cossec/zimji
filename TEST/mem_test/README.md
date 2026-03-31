# Memory test

This program copies a string from one place in memory to another

This is an excellent test for the CPU cache !

## Usage

You can directly run the pre-compiled binary `mem.bin`. For more options, look at the [simulator documentation](../../ISS/README.md#usage).

    ./ISS/build/src/zimji -s -v -c TEST/mem/mem.bin TEST/mem/data.bin 

> **ADVICE** To test the cache, don't forget to enable it with `-c`. To visualise the cache in action, also add the verbose option `-v` and step mode `-s`