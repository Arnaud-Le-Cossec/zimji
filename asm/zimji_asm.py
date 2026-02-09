import sys

mnemonics = {
    "STOP"  :{"op": 0,  "typ":4},
    "ADD"   :{"op": 1,  "typ":0},
    "SUB"   :{"op": 2,  "typ":0},
    "MUL"   :{"op": 3,  "typ":0},
    "DIV"   :{"op": 4,  "typ":0},
    "AND"   :{"op": 5,  "typ":0},
    "OR"    :{"op": 6,  "typ":0}, 
    "XOR"   :{"op": 7,  "typ":0},
    "SHL"   :{"op": 8,  "typ":0},
    "SHR"   :{"op": 9,  "typ":0},
    "SLT"   :{"op": 10, "typ":0},
    "SLE"   :{"op": 11, "typ":0},
    "SEQ"   :{"op": 12, "typ":0},
    "LOAD"  :{"op": 13, "typ":0},
    "STORE" :{"op": 14, "typ":0},
    "JMP"   :{"op": 15, "typ":1},
    "BRAZ"  :{"op": 16, "typ":2},
    "BRANZ" :{"op": 17, "typ":2},
    "SCALL" :{"op": 18, "typ":3},
}

registers = {
    "R0"    :(0,  False),
    "R1"    :(1,  False),
    "R2"    :(2,  False),
    "R3"    :(3,  False),
    "R4"    :(4,  False),
    "R5"    :(5,  False),
    "R6"    :(6,  False), 
    "R7"    :(7,  False),
    "R8"    :(8,  False),
    "R9"    :(9,  False),
    "R10"   :(10, False),
    "R11"   :(11, False),
    "R12"   :(12, False),
    "R13"   :(13, False),
    "R14"   :(14, False),
    "R15"   :(15, False),
    "R16"   :(16, False),
    "R17"   :(17, False),
    "R18"   :(18, False),
    "R19"   :(19, False),
    "R20"   :(20, False),
    "R21"   :(21, False),
    "R22"   :(22, False),
    "R23"   :(23, False),
    "R24"   :(24, False),
    "R25"   :(25, False),
    "R26"   :(26, False),
    "R27"   :(27, False),
    "R28"   :(28, False),
    "R29"   :(29, False),
    "R30"   :(30, False),
    "R31"   :(31, False)
}

prgIdx = 0
fileIdx = 0

class LabelMgr():
    # We use a dictionnary because they
    # have always the same access time.

    def __init__(self, preload:dict=None):
        if preload is None:
            self._labels = {}
        else:
            self._labels = preload

    def add(self, name: str, value: int, imm:bool=True):
        if name.upper() in self._labels:
            raise Exception(f"Label {name} was already defined at {self._labels[name][0]}!")
        else:
            self._labels[name.upper()] = (value, imm)
    
    def get(self, name:str):
        if name.upper() in self._labels:
            return self._labels[name][0], self._labels[name][1]
        else:
            raise Exception(f"Label {name} was not defined!")

class InstrMgr():

    def __init__(self, label:LabelMgr):
        self._lbl = label

    def get_operand(self, operands:str):
        operand_val = []
        operand_imm = []
        for operand in operands.split(','):
            try:
                #numeric value (dec, hex, bin)
                operand_val.append(int(operand, 0))
                operand_imm.append(True)
            except:
                #label or register
                l, i = self._lbl.get(operand.strip())
                operand_val.append(l)
                operand_imm.append(i)
        return operand_val, operand_imm

    def encode(self, mnemonic:str):
        instr = 0
        operand_typ = 0

        mn = mnemonic.split(' ')[0].upper()
        op = "".join(mnemonic.split(' ')[1:]).upper()

        #print(f"mn: {mn} op: {mnemonic.split(' ')[1:]}")

        if mn in mnemonics:

            operand_typ = mnemonics[mn]["typ"]
            operand_val, operand_imm = self.get_operand(op)

            print(f"{mn} (opcode:{mnemonics[mn]["op"]}, typ{operand_typ}), operands:{operand_val} imm:{operand_imm}", end="\n\t")

            instr |= (mnemonics[mn]["op"] & 0x1F) << 27
            if operand_typ == 0:
                instr |= (operand_val[0] & 0x1F) << 22
                instr |= (operand_imm[1] & 0x1) << 21
                instr |= (operand_val[1] & 0xFFFF) <<5
                instr |= (operand_val[2] & 0x1F)
            elif operand_typ == 1:
                instr |= (operand_imm[0] & 0x1) << 26
                instr |= (operand_val[0] & 0x1FFFFF) << 5
                instr |= (operand_val[1] & 0x1F)
            elif operand_typ == 2:
                instr |= (operand_val[0] & 0x1F) << 22
                instr |= (operand_val[1] & 0x3FFFFF)
            elif operand_typ == 3:
                instr |= operand_val[0] & 0xFFFFFFFF
            elif operand_typ == 4:
                pass

            return instr

        else:
            raise Exception(f"Instruction {mn} not recognized!")
        




if __name__ == '__main__':

    # Get arguments
    try:
        asm_filename = sys.argv[1]
        bin_filename = sys.argv[2]
    except:
        print("Could get arguments!")
        print("USAGE: zimji_asm.py <ASM source> <BIN output>")

    lblmgr = LabelMgr(preload=registers)
    instrmgr = InstrMgr(label=lblmgr)

    # Identify labels
    with open(asm_filename, 'r') as file:
        for line in file:
            fileIdx +=1
            try:
                #remove withspace and comments
                ls = line.strip().split(';')[0]
                if len(ls) == 0:
                    continue
                elif ls[-1] == ':':
                    lblmgr.add(ls.split(':')[0], prgIdx)
                else:
                    prgIdx += 1 
            except Exception as err:
                print(f"An error occured at line {fileIdx}!\n\t{err}")
                exit(-1)

    print(lblmgr._labels)

    # Identify instructions
    prgIdx = 0
    fileIdx = 0
    with open(asm_filename, 'r') as file:

        with open(bin_filename, 'w') as trgt:
            for line in file:
                fileIdx += 1
                try:
                    #remove withspace and comments
                    ls = line.strip().split(';')[0]

                    if len(ls) == 0:
                        continue
                    elif ls[-1] == ':':
                        continue
                    else:

                        #print(ls)
                        i = instrmgr.encode(ls)
                        print(f"\033[96m{prgIdx:#0{10}x}  {i:#0{10}x}\033[0m")

                        trgt.write(f"{prgIdx:#0{10}x} {i:#0{10}x}\n")
                        #hex(instrmgr.encode(ls))

                        prgIdx += 1 


                except Exception as err:
                    print(f"An error occured at line {fileIdx}!\n\t{err}")
                    exit(-1)

        