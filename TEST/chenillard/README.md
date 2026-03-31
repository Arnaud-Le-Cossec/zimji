# CHENILLIARD

This program rotates a string in memory

# Example

    [SCALL] String at &R1:  HELLO         
    [SCALL] String at &R1:   HELLO        
    [SCALL] String at &R1:    HELLO       
    [SCALL] String at &R1:     HELLO      
    [SCALL] String at &R1:      HELLO     
    [SCALL] String at &R1:       HELLO    
    [SCALL] String at &R1:        HELLO   
    [SCALL] String at &R1:         HELLO  
    [SCALL] String at &R1:          HELLO 
    [SCALL] String at &R1:           HELLO
    [SCALL] String at &R1: O          HELL
    [SCALL] String at &R1: LO          HEL
    [SCALL] String at &R1: LLO          HE
    ...

# Usage

You can directly run the pre-compiled binary `chenillard.bin`. For more options, look at the [simulator documentation](../../ISS/README.md#usage).

    ./ISS/build/src/zimji TEST/chenillard/chenillard.bin TEST/chenillard/data.bin 

> **NOTE** The data file is necessary as it contains the text for the game !

> **NOTE** This program does not stop by itself. Press `CTRL+C` to stop.