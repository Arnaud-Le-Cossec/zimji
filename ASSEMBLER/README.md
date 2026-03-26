# ZIMJI ASSEMBLER

This program compiles a code written in zimji **assemby** into zimji **machine code**.

## Usage

    ./zimji_asm SOURCE OUTPUT

- `SOURCE` Path to the assembly source file
- `OUTPUT` Path to the binary output file (PseudoBin format)

## Assembler syntax

### Case sensitivity

The assembler is NOT case sensitive.

### Comments

Comments are defined with a semi-colon `;`. Text after `;` is ignored

Example:

    ; This is a comment

### Labels (= Address alias)

Labels are replaced with their address at compile time. They are defined with `:` preceded with a unique name, that is not also an instruction or a register name.

Example:

    myLabel:

### Explicit labels (= Literal alias)

Explicit Labels are replaced with their value at compile time. They are defined with `=` preceded with a unique name, that is not also an instruction or a register name. A literal number is expected after `=`.

> An explicit label cannot be defined from another label. Mathematical operation are not supported

Example:

    myExplicitLabel=0x12

## Instruction Set

**Arithmetic and logic group**

| Mnmemonic | Description | Function | Format |
| --- | ----------- | --- | --- |
| add rs1, rs2, rd | addition | rd <- rs1 + rs2 | R |
| add rs, imm, rd | addition | rd <- rs + imm | I |
| sub rs1, rs2, rd | substraction | rd <- rs1 - rs2 | R |
| sub rs, imm, rd | substraction | rd <- rs - imm | I |
| mul rs1, rs2, rd | multiplication | rd <- rs1 * rs2 | R |
| mul rs, imm, rd | multiplication | rd <- rs * imm | I |
| div rs1, rs2, rd | division | rd <- rs1 / rs2 | R |
| div rs, imm, rd | division | rd <- rs / imm | I |
| and rs1, rs2, rd | Logical AND | rd <- rs1 & rs2 | R |
| and rs, imm, rd | Logical AND | rd <- rs & imm | I |
| or rs1, rs2, rd | Logical OR | rd <- rs1 \| rs2 | R |
| or rs, imm, rd | Logical OR | rd <- rs \| imm | I |
| xor rs1, rs2, rd | Logical XOR | rd <- rs1 ^ rs2 | R |
| xor rs, imm, rd | Logical XOR | rd <- rs ^ imm | I |
| shl rs1, rs2, rd | Shift left | rd <- rs1 << rs2 | R |
| shl rs, imm, rd | Shift left | rd <- rs << imm | I |
| shr rs1, rs2, rd | Shift right | rd <- rs1 >> rs2 | R |
| shr rs, imm, rd | Shift right | rd <- rs >> imm | I |

**Compare group**

| Mnmemonic | Description | Function | Format |
| --- | ----------- | --- | --- |
| slt rs1, rs2, rd | Set lower than | rd <- (rs1 < rs2)? 1:0 | R |
| slt rs, imm, rd | Set lower than | rd <- (rs < imm)? 1:0 | I |
| sle rs1, rs2, rd | Set lower equal | rd <- (rs1 <= rs2)? 1:0 | R |
| sle rs, imm, rd | Set lower equal | rd <- (rs <= imm)? 1:0 | I |
| seq rs1, rs2, rd | Set equal | rd <- (rs1 == rs2)? 1:0 | R |
| seq rs, imm, rd | Set equal | rd <- (rs == imm)? 1:0 | I |

**Jump and branch group**

| Mnmemonic | Description | Function | Format |
| --- | ----------- | --- | --- |
| jmp ra, rd | Jump and link register | rd <- PC+1; PC <- ra | JR |
| jmp addr, rd | Jump and link immediate | rd <- PC+1; PC <- addr | JI |
| braz rs, addr | Branch if zero | if(rs==0) {PC <- addr} | B |
| branz rs, addr | Branch if not zero | if(rs!=0) {PC <- addr} | B |

**Load and store group**

| Mnmemonic | Description | Function | Format |
| --- | ----------- | --- | --- |
| load ra, offset, rd | Read from memory | rd <- mem[ ra+offset ] | I |
| store ra, offset, rd | write into memory | mem[ ra+offset ] <- ra | I |

**System calls group**

| Mnmemonic | Description | Function | Format |
| --- | ----------- | --- | --- |
| Scall n | System call | - | S |
| Scall 0 | System call | r1 <- number from keyboard | S |
| Scall 1 | System call | print r1 on screen | S |
| Scall 3 | System call | print r1 as an ASCII (7bit) character | S |
| Scall 4 | System call | print null-terminated string pointed to by r1 | S |

## PseudoBin format

This assembler outputs in PseudoBin format:

    <address(hex)>:space:<value(hex)>

Example:

    0x00000000 0x0820000a
    0x00000001 0x7c0000ff
    0x00000002 0x62a00c8b

## Licence

Copyright © 2026 Arnaud LE COSSEC  

This project falls under the MIT licence. See [licence file](../LICENCE.md).
