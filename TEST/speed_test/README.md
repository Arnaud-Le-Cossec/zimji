# Speed test

This program loops 100000 times to estimate simulator performance

## Usage

You can directly run the pre-compiled binary `speed.bin`. For more options, look at the [simulator documentation](../../ISS/README.md#usage).

    ./ISS/build/src/zimji -f 0 TEST/speed_test/speed.bin

> **NOTE** It is important to set the simulator in free mode with no clock `-f 0` and **NO verbose `-v` or step mode `-s`**, otherwise the test will take centuries to complete